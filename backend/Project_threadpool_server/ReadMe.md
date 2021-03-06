# How to Use
1. 使用cmake
```bash
#先进入项目的根目录
cd YOUR_PROJECT_PATH/Project_threadpool_server
mkdir ./build
cd build 
cmake ..
make

#在build文件夹里就有class_server,和client两个可执行文件

分别在不同的终端中输入:
./class_server 9999

./client 0 9999

按照客户端提示输入字符串就能实现回射服务器功能
```

2. 使用bash
```bash
cd YOUR_PROJECT_PATH/Project_threadpool_server
cd ./src
bash build.sh
#就会在src目录下生成class_server和client两个可执行文件
```

# 回射服务器
使用的方法：
1. 多线程
2. 模拟Proactor事件处理模式
3. Linux 信号量、互斥锁
4. C++类的封装
5. Epoll IO复用函数，LT水平触发模式
6. cmake项目管理

## 需要注意的点
1. `threadpool.h` 文件 `line:60`， 当获得了互斥锁之后，还需要判断请求队列是否为空。这么做的目的是防止多个线程同时获得了信号量，又同时向队列拿任务对象的情况。
2. `模拟Proactor事件处理模式`，主线程只进行接受新连接和对数据进行读、写操作， 子线程只处理业务逻辑（在这个项目中，子线程将`readbuf`里的数据拷贝到`writebuf`上，并注册写事件，通知主线程去对调用`write()`将`writebuf`上的数据发回去客户端上面。）。因此由子线程注册写事件，主线程写完后重新注册读事件。
3. 还有更加高效的方法：使用两次[splice()函数](https://github.com/aoaforever/linux-C-Backend-Develop/blob/main/%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B/%E9%AB%98%E7%BA%A7IO%E5%87%BD%E6%95%B0.md#:~:text=%E8%80%8C%E8%AE%BE%E8%AE%A1%E7%9A%84%E3%80%82-,splice%E5%87%BD%E6%95%B0%E4%B8%8E%E9%9B%B6%E6%8B%B7%E8%B4%9D,-splice%20%E5%87%BD%E6%95%B0%E7%94%A8%E4%BA%8E)和管道来实现零拷贝的回射服务器。从而避免从内核缓冲区拷贝数据到用户缓冲区，再从用户缓冲区拷贝的内核缓冲区的情况。不过本人实现这个项目的目的是为了更多的应用场景：比如需要用户态来处理HTTP请求业务，因此是不可避免的需要将内核缓冲区的数据拷贝到用户态上。
4. 有些读者可能会不容易发现为什么`threadpool.h`文件没有对应的`.cpp`实现文件。这是因为`threadpool.h`文件中的`threadpool类`是一个模板类，在`C++ Primer Plus`中`第14章14.4.1节`中已经说明：**不能将模板成员函数放在独立的实现文件中，由于模板不是函数，它们不能单独编译。模板必须与特定的模板实例化请求一起使用。为此，最简单的方法是将所有模板信息放在一个头文件中，并在要使用这些模板的文件中包含该头文件**。本人也是花了2天时间才发现这个细节，cmake编译的时候一直报错：`undefined reference`错误。
5. cmake如何添加`-lpthread`选项？ `set(CMAKE_CXX_FLAGS "std=c++11 -pthread")`,关于这个问题，网上有很多不同的做法，我也没搞太懂。
