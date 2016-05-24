/*************************************************************************
	> File Name: oncerun.c
	> Author: 
	> Mail: 
	> Created Time: 2016年04月25日 星期一 20时16分30秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void run(void)
{
    printf("Function run is running in thread %u\n",pthread_self());
}
void * thread1(void * arg)
{
    pthread_t thid=pthread_self();
    printf("current thread's ID is %u\n",thid);
    pthread_once(&once,run);
    printf("thread1 ends.\n");
}
void *thread2(void * arg)
{
    pthread_t thid=pthread_self();
    printf("current threat's ID is %u\n",thid);
    pthread_once(&once,run);
    printf("thread2 ends.\n");
}
int main(void)
{
    pthread_t thid1,thid2;
    pthread_create(&thid1,NULL,thread1,NULL);
    pthread_create(&thid2,NULL,thread2,NULL);
    sleep(3);
    printf("main thread exit!\n");
    exit(0);
}
