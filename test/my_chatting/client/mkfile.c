/*************************************************************************
	> File Name: mkfile.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月11日 星期三 19时16分51秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(void)
{
    int fd1,fd2;
    if(  mkdir( "MsgRead" , S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP ) == -1)
    {
        perror("Created directorty MsgRead  wrong!");
        exit(1);
    }
    if(  mkdir( "./MsgRead/usr" , S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP ) == -1)
    {
        perror("Created directorty usr wrong!");
        exit(1);
    }
    if(  mkdir( "./MsgRead/grp" , S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP ) == -1)
    {
        perror("Created directorty grp  wrong!");
        exit(1);
    }
    if( (fd1 = creat( "./MsgRead/unread" ,  S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP ) ) == -1)
    {
        perror("Created passwd.txt wrong!");
        exit(1);
    }
    return 0;
}
