#pragma once
#include <string.h>
#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include <assert.h>
using namespace std;


class User{
public:
    int fd;
    static const int BUF_SIZE = 1024;//因为每个user对象的buffer_size都是一样的，所以定义为静态变量
    char *readbuf;
    char *writebuf;
    static int epoll_fd;//每个任务都有一个管理他的epoll_fd内核事件表
    void clear_readbuf();
    void clear_writebuf();
    bool Uread();
    void Uwrite();
    void process();
    User();
    User(int fd);
    ~User();
};

