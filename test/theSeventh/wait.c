/*************************************************************************
	> File Name: wait.c
	> Author: 
	> Mail: 
	> Created Time: 2016年04月22日 星期五 21时42分47秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    pid_t   pid;
    char    * msg;
    int     k;
    int     exit_code;

    printf(">>Study how to get exit code.\n");
    pid=fork();
    switch(pid)
    {
        case 0:
            msg = "Child process is running !!!";
            k = 5;
            exit_code=37;
            break;
        case -1:
            perror(">Process creatint failed!\n");
            exit(-1);
            break;
        default:
            exit_code=0;
            break;
    }
    /*子进程和父进程都会执行以下代码
    * 子进程的PID为0,父进程的PID为子进程的id*/
    if(pid != 0)
    //父进程等待子进程的结束
    {
        int     stat_val;
        pid_t   child_pid;
        printf("===>Partent start at here!!!\n"); 
        child_pid = wait(&stat_val);
        printf(">Child process has exited,pid = %d\n",child_pid);
        if(WIFEXITED(stat_val))
            printf(">Child exited with code %d\n",WEXITSTATUS(stat_val));
        else
            printf(">Child exited abnormally\n");
    }
    else
    {//子进程暂停5秒，在这个过程中可以运行命令ps aux查看父进程的状态：
        while(k-->0)
        {
            puts(msg);
            sleep(1);
        }
    }
    exit(exit_code);
}
