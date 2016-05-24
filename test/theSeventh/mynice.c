/*************************************************************************
	> File Name: mynice.c
	> Author: 
	> Mail: 
	> Created Time: 2016年04月23日 星期六 09时58分48秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/resource.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(void)
{
    pid_t   pid;
    int     stat_val = 0;
    int     oldpri,newpri;

    printf(">>>nice study:\n");
    pid = fork();
    switch(pid)
    {
        case 0:
            printf("Child is running,curPID is %d , ParentPID is %d \n",pid,getpid());
            oldpri = getpriority(PRIO_PROCESS,0);
            printf("Old priority = %d  \n",oldpri);
            newpri = nice(2);
            printf("New priority = %d \n",newpri);
            exit(0);
        case -1:
            perror("Process creation failed.\n");
            exit(-1);
        default:
            printf("Parent is running , ChildPID is %d , ParentPID is %d\n",pid,getpid());
            break;
    }
    wait(&stat_val);
    exit(0);
}
