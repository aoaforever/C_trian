#include<stdio.h>
#include <string.h>
#include <stdarg.h>
#include <iostream>
// using namespace std;

void parse_request_line(char *text){
    
    char* m_url = strpbrk(text," \t");//空格或者\t
    printf("下标：%d,将会输出包括%d以后的字符串\n",m_url-text,m_url-text);
    printf("%s\n",m_url);
    *m_url++ = '\0';
    printf("%s\n",text);

    char *method = text;
    printf("method:%s",method);
    printf("%d\n",strcasecmp(method,"GET"));// ' ' 的ascii码为32
    // if(strncmp("GET / HTTP/1.0\r\n","GET",3)==0){
    //     printf("yes");
    // }

    // *m_url++ = '\0';
    // printf("%s\n",m_url);
    // printf("%d\n",strspn(m_url," \t"));

    m_url += strspn(m_url," \t");//"123456.jpg HTTP/1.0" 或 / HTTP/1.0
    // printf("%s\n",m_url);


    char *m_version = strpbrk(m_url," \t");//" HTTP/1.0"
    // printf("%s\n",m_version);
    *m_version++ = '\0';//"HTTP/1.0"
    // printf("%s\n",m_version);
    m_version += strspn(m_version," \t");//"HTTP/1.0"
    // printf("%s\n",m_version);

    // char m_url[20] = "/ HTTP/1.0";
    strcat(m_url,"judge.html");
    printf("%s\n",m_url);







}


void add_response(const char* format, ...){
    const int WRITE_BUFFER_SIZE = 1024;
    char m_write_buf[WRITE_BUFFER_SIZE];
    
    va_list arg_list;//定义一个va_list型的变量，这个变量是指向参数的指针
    va_start(arg_list,format);//用va_start宏初始化变量,这个宏的第二个参数是第一个可变参数的前一个参数,是一个固定的参数
    int len = vsnprintf(m_write_buf,WRITE_BUFFER_SIZE,format,arg_list);
    va_end(arg_list);
    puts(m_write_buf);
    printf("输出了%d个字符",len);
}

int main(int c, char **v){
    // char a = ' ';
    // printf("%d\n",a);
    // char query[] = 
    // "GET / HTTP/1.0\r\n";
    // "Host: www.google.com\r\n"
    // "\r\n";

    // cout<<query<<endl;
    // printf("%s\n",query);
    // parse_request_line(query);

    add_response("sadsadwakkk\n,%s,%d,%d,%d,%c,%c","asd",2,3,4,getchar(),getchar());
    return 0;

}
