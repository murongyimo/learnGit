/*************************************************************************
	> File Name: my_create.c
	> Author: 
	> Mail: 
	> Created Time: 2016年04月23日 星期六 10时37分16秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
    int fd;
    if((fd=open("example_62.c",O_CREAT|O_EXCL,S_IRUSR|S_IWUSR)==-1))
    //if((fd=creat("example_62.c",S_IRWXU))==-1)
    {
        //perror("open");
        printf("open:%s  with errno:%d\n",strerror(errno),errno);
        exit(1);
    }
    else
    {
        printf("create file success!\n");    
    }
    close(fd);
    return 0;
}
