#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;
/*下面是一段利用条件变量实现父线程检查子线程是否执行完毕的代码。
请分析这段代码可能存在的问题？
如果要解决这个问题应该如何修改？*/

/*
https://blog.csdn.net/wanguofeng8023/article/details/124832690

*/
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thr_exit(){//子线程
    sleep(4);
    pthread_mutex_lock(&m);
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
}

void thr_join(){//主线程
    sleep(3);
    pthread_mutex_lock(&m);
    pthread_cond_wait(&c,&m);
    // while(pthread_cond_wait(&c,&m));//等待某个线程释放条件变量，先解锁，然后等待，如果被唤醒，则枷锁
    pthread_mutex_unlock(&m);//获得锁之后，直接释放锁。
}

void *child(void *arg){
    printf("child\n");
    thr_exit();
    return NULL;
}

int main(int argc, char const *argv[])
{
    printf("parent begin\n");
    pthread_t p;
    pthread_create(&p,NULL,child,NULL);
    thr_join();
    // pthread_join(p,NULL);
    printf("parent end\n");
    return 0;
}

/*
parent begin
child
然后不动了

主要问题还是，如果子线程比主线程先运行，那么子线程发出的V操作，主线程会收不到。
*/
