/*************************************************************************
	> File Name: fork.c
	> Author: 
	> Mail: 
	> Created Time: 2016年04月20日 星期三 19时45分44秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main(void)
{
    pid_t pid;
    printf(">>Pross create study:\n");
    pid=fork();
    switch(pid)
    {
        case 0:
        while(1){
            printf("A backgroucd Process,PID: %d,ParentID:%d\n",getpid(),getppid());
            sleep(3);
        }
            break;
        case -1:
            perror("process creation failed\n");
            exit(-1);
            break;
        default:
            printf("I am parent process,my PID is %d\n",getpid());
            exit(0);
            break;
    }
}
