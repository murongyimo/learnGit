/*************************************************************************
	> File Name: test_select.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月07日 星期六 23时05分20秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>

void display_time( const char *string )
{
    int seconds;
    seconds = time( ( time_t * )NULL );
    printf("%s,%d\n",string,seconds);
}

int main( void )
{
    fd_set  readfds;
    struct timeval timeout;
    int     ret;

    //监视文件描述符0是否有输入，文件描述符0表示输入，即键盘输入
    FD_ZERO( &readfds );
    FD_SET( 0 , &readfds );

    //设置阻塞时间为10秒
    timeout.tv_sec = 10 ;
    timeout.tv_usec = 0 ;

    while( 1 ){
        display_time("before select");
        ret = select( 1 , &readfds , NULL , NULL , &timeout );
        display_time("after select");

        switch( ret ){
            case 0 :
                printf("No data in ten seconds.\n");
                exit( 0 );
                break;
            case -1 :
                perror( "select" );
                break;
            default:
                getchar();
                printf("Data is avaliable now.\n");
        }
    }
    return 0;
}
