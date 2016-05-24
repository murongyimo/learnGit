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
    char * msg;
    int k;

    printf(">>Pross creation study:\n");
    pid=fork();
    switch(pid)
    {
        case 0:
            msg="Child Process is running!";
            k=3;
            break;
        case -1:
            perror("Process creation failed.");
            break;
        default:
            msg="Parent Process is running!";
            k=5;
        break;
    }

    while(k>0)
    {
        puts(msg);
        sleep(1);
        k--;
    }
    exit(0);
}
