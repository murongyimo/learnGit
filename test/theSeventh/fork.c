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
            printf("Child Process is running ,the curPid is %d,Parent is %d\n",pid,getppid());
            break;
        case -1:
            printf("Process creation failed.\n");
            break;
        default:
            printf("Parent process is running ,ChildPid is %d,ParentPid is %d\n",pid,getpid());
            break;
    }
    exit(0);
}
