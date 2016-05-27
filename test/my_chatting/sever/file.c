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
#include<unistd.h>
#include<fcntl.h>

int main(void)
{
    
        if(  mkdir( "Grp" , S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP ) == -1)
    {
        perror("Created directorty usr wrong!");
        exit(1);
    }
        if( (creat( "passwd.txt" ,  S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP ) ) == -1)
    {
        perror("Created passwd.txt wrong!");
        exit(1);
    }
    
        if( (creat( "usr_num.txt" ,  S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP ) ) == -1)
    {
        perror("Created usr_num.txt wrong!");
        exit(1);
    }    
        if( (creat( "log.txt" ,  S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP ) ) == -1)
    {
        perror("Created log.txt wrong!");
        exit(1);
    }    


    return 0;
}
