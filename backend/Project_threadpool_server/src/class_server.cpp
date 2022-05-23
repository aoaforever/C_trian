#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <cassert>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>


#include "User.h"
#include "threadpool.h"


#include <errno.h>
using namespace std;



class Server{
public:
    int serv_socket;
    int epoll_fd;
    
    struct sockaddr_in serv_addr;
    const static int MAX_EVENTS_NUMBER = 1000;
    const static int MAX_FD = 65536;
    const static int MAX_BYTES = 1024;
    User *users;
    epoll_event events[MAX_EVENTS_NUMBER];

    //线程池相关
    threadpool<User>  *m_pool;

    char *file_name;
    struct stat buffer;

    Server(char* port){
        m_pool = new threadpool<User>();
        users = new User[MAX_FD];

        serv_socket = socket(AF_INET,SOCK_STREAM,0);
        assert(serv_socket>=0);

        //TIME_WAIT状态也能立即重用该地址。
        int flag = 1;
        setsockopt(serv_socket,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag));

        memset(&serv_addr,0,sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(atoi(port));

        int ret=0;
        ret = bind(serv_socket,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
        assert(ret>=0);

        ret = listen(serv_socket,5);
        assert(ret>=0);

        epoll_fd = epoll_create(1);
        assert(epoll_fd!=-1);
        add_fd(epoll_fd,serv_socket,EPOLLIN);
        User::epoll_fd = epoll_fd;


    }

    ~Server(){
        close(epoll_fd);
        close(serv_socket);
        delete []users;
    }

    void send_png(int socketfd){
        char file_path[MAX_BYTES]= "/home/aoa_vm/workplace/backend/img_001_SRF_4_HR.png";
        if(stat(file_path,&buffer)==-1){
            perror("非法的路径名");
            return ;
        }
        file_name = basename(file_path);
        struct node{
            int len;
            char name[100];
        }node;
        node.len = buffer.st_size;
        strcpy(node.name,file_name);
        char temp[MAX_BYTES];
        memcpy(temp,&node,sizeof(node));
        write(socketfd,temp,sizeof(temp));

        //开始向对方发送文件
        int fp = open(file_path,O_CREAT|O_RDONLY, S_IRUSR|S_IWUSR);

        printf("开始发送文件:%s\n",node.name);
        sendfile(socketfd,fp,0,buffer.st_size);
        printf("文件发送完毕\n");
        close(fp);
        
    }

    void add_fd(int epollfd, int fd,int ev){
        struct epoll_event event;
        event.events = ev | EPOLLRDHUP;
        event.data.fd = fd;
        epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
    }
    void mod_fd(int epollfd, int fd, int ev){
        struct epoll_event event;
        event.events = ev | EPOLLRDHUP;
        event.data.fd = fd;
        epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event);
    }

    bool dealclinetdata(){
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);

        int connfd = accept(serv_socket,(struct sockaddr*)&client_address,&client_len);
        if(connfd<0){
            cerr<<"accept error , errno is: "<<errno<<endl;
            return false;
        }
        users[connfd].fd = connfd;
        add_fd(epoll_fd,connfd,EPOLLIN);
        
        return true;
    }
    void dealwithread(int sockfd){
        if(users[sockfd].Uread()){
            m_pool->append(&users[sockfd]);
        }
        
        
    }
    void dealwithwrite(int sockfd){
        users[sockfd].Uwrite();
        
    }
     
    void eventLoop(){
        bool stop_server = false;
        while(!stop_server){
            int number = epoll_wait(epoll_fd,events,MAX_EVENTS_NUMBER,-1);
            if(number<0 &&errno!=EINTR){
                cerr<<"epoll failure"<<endl;
                break;
            }
            for(int i=0;i<number;i++){
                int sockfd = events[i].data.fd;

                //处理新到的客户连接
                if(sockfd==serv_socket){
                    cout<<"新来一个连接"<<endl;
                    bool flag = dealclinetdata();
                    if(false == flag) continue;
                }
                else if(events[i].events &(EPOLLRDHUP | EPOLLHUP | EPOLLERR)){
                    //服务器关闭连接
                    cout<<"对方关闭了连接,fd: "<<sockfd<<endl;
                    epoll_ctl(epoll_fd,EPOLL_CTL_DEL,sockfd,0);
                    
                    close(sockfd);
                }
                else if(events[i].events & EPOLLIN){
                    cout<<"触发了读事件"<<endl;
                    dealwithread(sockfd);
                }
                else if(events[i].events & EPOLLOUT){
                    cout<<"触发了写事件"<<endl;
                    dealwithwrite(sockfd);
                }
            }
        }
    }

};


int main(int argc,char* argv[]){
    assert(argc==2);
    Server s(argv[1]);
    s.eventLoop();
    return 0;
}