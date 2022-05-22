#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
using namespace std;

#define BUF_SIZE 1024
void errorhandling(const char *message);

int main (int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[BUF_SIZE];
	int str_len = 0, idx = 0, read_len = 0;

	if (argc != 3 )
	{
		cout<<"Usage: "<<argv[0]<<" <IP> <port> "<<endl;
		exit(0);
	}

	sock = socket(AF_INET,SOCK_STREAM,0);
	if ( sock == -1){
		errorhandling("socket() error;");
	}
	
	memset(&serv_addr, 0 , sizeof( serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);//将点分十进制的ip地址字符串转换为 大端的网络字节序整数
	serv_addr.sin_port = htons(atoi(argv[2]));//先将字符串转换成整数

	if ( connect(sock, (struct sockaddr* )&serv_addr, sizeof(serv_addr) ) == -1 ){
		errorhandling("connect error;");
	}
	else 
	{
		cout<< "connected... "<<endl;
	}


	while (1)
	{
		cout<<"Input Q/q to exit."<<endl;
		fgets(message, BUF_SIZE, stdin);
		if( !strcmp(message, "q\n")  || !strcmp( message, "Q\n") )
		{
			break;
		}

		write(sock, message, strlen(message));
		
		// char temp[1024];
		// struct node{
		// 	int len;
		// 	char name[100];
		// }node;
		// memset(temp,0,sizeof(temp));
		// read(sock,temp,sizeof(temp));//先接收一个结构体，再接收文件
		// memcpy(&node,temp,sizeof(node));//只读node结构体的字节。很巧妙
		// sprintf(temp,"./file_recv/%s",node.name);
		// printf("文件保存路径: %s\n",temp);
		// //创建文件
		// // FILE *fp = fopen(temp,"wb");
		// ofstream fpout(temp,ios_base::binary);
		// // if(fp==NULL){
		// // 	// cerr<<"Cannot open file"<<endl;
		// // 	perror("Cannot open file  \n");
		// // 	exit(1);
		// // }
		// if(!fpout.is_open()){
		// 	// cerr<<"Cannot open file"<<endl;
		// 	perror("Cannot open file  \n");
		// 	exit(1);
		// }
		// //把数据写入文件
		// printf("Start receive file: %s from %d fd\n",temp,sock);

		// int n;
		// int sum=0;
		// char buf[1024];
		// memset(buf,0,sizeof(buf));
		
		// while(1){
		// 	n= read(sock,buf,1024);
		// 	if(n<0) {
		// 		perror("接收数据错误： ");
		// 		break;
		// 	}
		// 	fpout.write(buf,n);
		// 	// fpout.flush();
		// 	// fwrite(buf,sizeof(char),n,fp);
		// 	sum += n;
		// 	// cout<<sum<<"  ";
		// 	memset(buf,0,sizeof(buf));
		// 	if(sum>=node.len){
		// 		break;
		// 	}
			
		// }
		
		// printf("Receive Success\n");
		// // fclose(fp);
		// fpout.close();


		str_len = read( sock, message, BUF_SIZE -1);//因为当客户端发过去的时候，服务器也发送了数据.
		message[str_len] = '\0';
		printf(" Message from server : %s , 一共%d字节\n",message,str_len);
	}
	cout<<"closing socket.."<<endl;
	close(sock);
	cout<<"closed."<<endl;
	return 0;





}

void errorhandling(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
