/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月21日 星期六 23时48分20秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<dirent.h>

#define MAX_NAME_SIZE 20    //最长用户名
#define MAX_USR 50          //最大在线人数
#define LISTEN_NUM 20       //等待队列长度
#define MAXSIZE 300         //最大缓存区
#define MAX_PASSWD_SIZE 20      //最大密码长度
#define MAX_MESSAGE_BUF 200     //最长信息缓存
#define MAX_TIME_SIZE 30        //存放时间数组长度
#define MAX_GRP_USR 20          //存放群聊人数上限
#define MAXPATH 100             //最大路径长度
#define PORT 4507

typedef struct usr_node{
    int state;//在线为1,不在线为0
    int connfd;
    char name[MAX_NAME_SIZE];
}usrNode;


int Recv_msg( int fd );
void Chg_usr_num( int num );
int Get_usr_num();
int Is_usr( char * name );
int Is_online( char * name );
int Add_usr( char * name , char * passwd );
int LogIn_usr( char * name , char * passwd );
void Log_Out_usr( int id );
void get_Time( char * now_time );
void Exit_Grp( char * grp_name , int id );
int Join_Grp( char * grp_name , int id );
int Create_Grp( char * grp_name , int id );
int Is_Grp( char * grp_name );
void Conbine_msg( char * buf , char * name , char * type , char * msg );
void Cut_msg( char * buf , int * id , char * type , char * name , char * msg );
int Check_usr( char * name , char * passwd );
void make_pthread( int * connfd );
void Grp_talk( int id , char * name , char * msg );

int listenfd;       //监听套接字
usrNode USR[MAX_USR];
//int USR_NUM = 0     //当前系统中已申请的用户个数

#include"Usr.c"         //处理用户操作
#include"group.c"       //处理群操作
#include"msg.c"



int main( void )
{
    pthread_t thrid;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t len;
    time_t ticks;

    int connfd , optval = 1;
    
    memset( USR , 0 , MAX_USR * sizeof(struct usr_node) );
    if((listenfd = socket( AF_INET , SOCK_STREAM , 0 )) <0 ){
        perror("listenfd socket create");
        exit(1);
    }
    
    if(setsockopt( listenfd , SOL_SOCKET , SO_REUSEADDR , (void*)&optval , sizeof(int)  ) < 0 ){
        perror("setsockopt error");
        exit(1);
    }    
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl( INADDR_ANY );
    serv_addr.sin_port = htons(PORT);
    bind( listenfd , ( struct sockaddr * )&serv_addr , sizeof( struct sockaddr_in ) );
    if(listen( listenfd , LISTEN_NUM ) < 0 ){
        perror("listen error");
        exit(1);
    }
    
    while( 1 ){
        len = sizeof( cli_addr );
        if((connfd = accept( listenfd , ( struct sockaddr * )&cli_addr , &len )) < 0 ){
            perror("accept error");
            exit(1);
        }else{
            printf("accept==>IP:%s\tPort:%d\n",inet_ntoa((cli_addr.sin_addr)) , cli_addr.sin_port);
        }
        pthread_create( malloc(sizeof(pthread_t)) , NULL , (void *)&make_pthread , (void *)&connfd );

    }
    
    return 0;
    
}
