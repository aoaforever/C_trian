#include "User.h"

using namespace std;

int User::epoll_fd =-1;

void mod_fd(int epollfd, int fd, int ev){
    struct epoll_event event;
    event.events = ev | EPOLLRDHUP;
    event.data.fd = fd;
    epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event);
}


void User::clear_readbuf(){
    memset(readbuf,0,sizeof(char)*BUF_SIZE);
}

void User::clear_writebuf(){
    memset(writebuf,0,sizeof(char)*BUF_SIZE);
}


bool User::Uread(){
    cout<<"正在读事件"<<endl;
    //对方发来了一段视频，将其读取并保存下来。
    
    clear_readbuf();
    cout<<"client fd: "<<fd<<endl;
    ssize_t isize = read(fd,readbuf,sizeof(char)*BUF_SIZE);
    // assert(isize>0);
    // cout<<"recv "<<isize<<" bytes from "<<fd<<": "<<string(readbuf)<<endl;
    // // send_png(sockfd);
    // //读完后立刻注册写事件，做一个回射服务器
    // mod_fd(epoll_fd,fd,EPOLLOUT);
    return true;
}

void User::Uwrite(){
    //服务器向sockfd主动发送视频文件
    cout<<"正在进行写事件"<<endl;
    
    size_t isize = write(fd,writebuf,strlen(writebuf));
    assert(isize>0);
    //写完后，再让他监听对方发来的消息
    mod_fd(epoll_fd,fd,EPOLLIN);
}

void User::process(){
    //模拟proactor模式，主线程执行读写数据到buf里，子线程对buf进行业务处理
    cout<<"Recive from "<<fd<<", Total "<<strlen(readbuf)<<" Bytes, content: "<<string(readbuf)<<endl;
    //将读到的数据写到写buf里
    clear_writebuf();
    strcpy(writebuf,readbuf);
    mod_fd(epoll_fd,fd,EPOLLOUT);
}

User::User(){
    readbuf = new char[BUF_SIZE];
    writebuf = new char[BUF_SIZE];
    clear_readbuf();
    clear_writebuf();
}

User::User(int fd): fd(fd){}

User::~User(){
    delete []readbuf;
    delete []writebuf;
}