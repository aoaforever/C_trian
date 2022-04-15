#ifndef MIN_HEAP
#define MIN_HEAP

#include <iostream>
#include <netinet/in.h>
#include <time.h>
/*对时间堆而言， 添加一个定时嚣的时间复杂度是 O (logn)，删除
一个定时稽的时间复杂度是 O ( 1 ），执行一个定时器的时间复杂度是 O( I ）.因此， 时间堆
的效率是很高的 ．*/
using std::exception;

#define BUFFER_SIZE 64

class heap_timer;//前向声明
//绑定socket和定时器
struct client_data{
    sockaddr_in address;
    int sockfd;
    char buf[BUFFER_SIZE];
    heap_timer* timer;
};

//定时器类
class heap_timer{
public:
    heap_timer(int delay){
        expire = time(NULL)+delay;
    }
public:
    time_t expire;//定时器生效的绝对时间
    void (*cv_func)(client_data*);//定时器的回调函数
    client_data* user_data;//用户数据
};

//时间堆类
class time_heap{
private:
    heap_timer** array;//堆数组，数组的每个元素都指向heap_timer
    int capacity;//堆数组的容量
    int cur_size;//堆数组当前包含元素的个数

public:
    //构造函数之一：初始化一个大小为cap的空堆
    time_heap(int cap) throw (std::exception) : capacity(cap),cur_size(0){
        array = new heap_timer* [capacity];//创建堆数组
        if(!array){
            throw std::exception();
        }

        for(int i = 0 ; i<capacity; ++i){
            array[i] =NULL;
        }
    }

    //构造函数之二，用已有数组来初始化堆
    time_heap(heap_timer** init_array, int size, int capacity) throw (std::exception):
        cur_size(size), capacity(capacity){
            if(capacity<size){
                throw std::exception();
            }

            array = new heap_timer* [capacity];//创建堆数组
            if(!array){
                throw std::exception();
            }
            for(int i=0;i<capacity;++i){
                array[i]=NULL;
            }
            if(size!=0){
                //初始化堆数组
                for(int i =0; i<size; ++i){
                    array [i] = init_array[i];
                }
                for(int i =(cur_size-1)/2; i>=0; --i){
                    //对数组中的第[(cur_size-1)/2] ~ 0 个元素执行下滤操作
                    percolate_down(i);//最小堆的下滤操作
                }
            }
        }
        //销毁时间堆
        ~time_heap(){
            for(int i =0; i<cur_size; ++i){
                delete array[i];
            }
            delete [] array;
        }

public:
    //添加目标定时器timer
    void add_timer(heap_timer* timer) throw (std::exception){
        if(!timer){
            return ;
        }
        if(cur_size >= capacity){//如果当前堆数组容量不够，则将其扩大1倍
            resize();
        }
        //新插入了一个元素，当前堆大小加1，hole是新建空穴的位置
        int hole = cur_size++;
        int parent =0;
        //对从空穴到根节点的路径上的所有节点执行上滤操作
        for(;hole>0;hole = parent){
            parent = (hole -1 )/2;
            if( array[parent]->expire <= timer->expire){
                break;
            }
            array[hole] =array[parent];
        }
        array[hole] = timer;
    }

    //删除目标定时器timer
    void del_timer(heap_timer* timer){
        if(!timer){
            return ;
        }
        //仅仅将目标定时器的回调函数设置为空，即所谓的延迟销毁，
        //这将节省真正删除该定时器造成的开销，但这样做容易使堆数组膨胀
        timer->cv_func=NULL;
    }

    //获得堆顶部的定时器
    head_timer* top() const{
        if (empty()){
            return NULL;
        }
        return array[0];
    }

    //删除堆顶部的定时器
    void pop_timer(){
        if(empty()){
            return ;
        }
        if(array[0]){
            delete array[0];
            //将原来的堆顶元素替换为堆数组中最后一个元素
            array[0] = array[--cur_size];
            percolate_down(0);//堆新的堆顶元素执行下滤操作
        }
    }

    //心搏函数
    void tick(){
        heap_timer* tmp = array[0];
        time_t cur = time(NULL);//循环处理堆中到期的定时器
        while(!empty()){
            if(!tmp){
                break;
            }
            //如果堆顶定时器没到期，则推出循环
            if(tmp->expire > cur){
                break;
            }

            //否则就执行堆顶定时器中的任务
            if(array[0]->cv_func){
                array[0]->cv_func(array[0]->user_data);
            }

            //将堆顶元素删除，同时生成新的堆顶定时器
            pop_timer();
            tmp = array[0];
        }
    }
    bool empty() const {
        return cur_size==0;
    }
private:
    //最小堆的下滤操作，它确保堆数组中以第hole个节点作为根的子树拥有最小堆性质
    void percolate_down(int hole){
        heap_timer* temp = array[hole];
        int child =0;
        for(;(hole*2+1)<=(cur_size-1); hole = child){
            child = hole*2+1;
            if((child<(cur_size-1)&& (array[child+1]->expire<array[child]->expire))){
                ++child;//右孩子更小
            }
            if(array[child]->expire <temp->expire){//孩子更小,如果孩子<临时点，则空穴填孩子
                array[hole] = array[child];
            }
            else {
                break;
            }
        }
        array[hole] =temp;
    }
    //将堆数组容量扩大1倍
    void resize() throw (std::exception){
        heap_timer** temp = new heap_timer* [2*capacity];
        for(int i=0; i<2*capacity;++i){
            temp[i] = NULL;
        }
        if(!temp){
            throw std::exception();
        }

        capacity = 2*capacity;
        for(int i=0;i<cur_size;i++){
            temp[i] = array[i];
        }
        delete [] array;
        array = temp;
    }
};

#endif