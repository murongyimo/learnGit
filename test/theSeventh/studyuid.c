/*************************************************************************
	> File Name: studyuid.c
	> Author: 
	> Mail: 
	> Created Time: 2016年04月22日 星期五 22时34分47秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>

extern int errno;

int main()
{
    int fd;
    printf(">>>UID study:\n");
    printf(">Process's uid = %d,euid = %d\n",getuid(),geteuid());
    //strerror函数获得指定错误码的信息：
    if((fd = open("./test.c",O_RDWR))==-1)
    {
        //printf(">Open failure,erro is %d:%s\n",errno,strerror(errno));
        perror("Open:");
        exit(1);
    }
    else
        printf(">Open successfully!\n");
    close(fd);
    exit(0);
}
