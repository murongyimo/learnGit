/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月18日 星期三 19时22分38秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<time.h>

#define USR_CLASS 0             //用户类型
#define GRP_CLASS 1             //群组类型

#define MAX_TIME_SIZE 30        //存放时间数组长度
#define MAXPATH 100             //最大路径长度

#define MAX_MESSAGE_BUF 200     //最长信息缓存
#define MAX_NAME_SIZE 20        //最大用户名长
#define MAX_PASSWD_SIZE 20      //最大密码长度
#define MAXSIZE 300             //最大缓存区
#define UNREAD 300              //一条未读信息缓存长度

#define BUF 500                 //socket上的信息缓存
#define HOST_ADDR "127.0.0.1"//ip地址
#define PORT 4507              //端口号



typedef struct node_msg{
    //未读信息节点
    int cnt;
    int type;
    char name[MAX_NAME_SIZE];
    struct node_msg * next;
}msgNode;

int Is_Friend( char * name , int type );
int Add_friend( char * name , int type );
void Read_msgRecord( char * name  , int message_class );
void Write_msgRecord( char * name ,char * msg_name , char * msg , char * time , int message_class );
void Print_msgDir(int message_class);
msgNode * Init_unread();
void ADD_unread( msgNode * h , msgNode * s );
void Del_unread( msgNode * h , msgNode * p );
msgNode * Find_unread( msgNode * h , char * name , int type );
void Delete_list( msgNode * h );
msgNode * Create_unreadNode( int cnt , int type ,char * name );
void Write_unread( msgNode * h );
msgNode * Read_unread();
void Print_unread( msgNode * h );
int Check_unread( msgNode * h ,char * name , int type );
void MsgIn_unread( msgNode * h , int cnt , int type , char * name );
void Clear_unread( msgNode * h );
void Start_form();
void register_form();
void Select_form();
void Usr_form();
void Group_form();
void FriendMsg_form();
void AddFriend_form();
void DelFriend_form();
void Select_ChatFriend_form();
void Chat_form();
void CreateGrp_form();
void UnreadMsg_form();
void Read_msgRecord( char * name  , int message_class );
void Write_msgRecord( char * name ,char * msg_name , char * msg , char * time , int message_class );
void Print_msgDir( int message_class );
void Cut_msg( char * buf , char * name , char * type , char * msg );
void get_Time( char * now_time );
void process_msg( char * buf );
void Comb_msg( char * buf , char * name , char * type , char * msg );
int Get_unread_cnt( msgNode * h );
int Friend_apply( char * name );
void watch_friendApply();
void handle_friendApply();
int count_friendApply();
void write_friendApply_result( char * name , int type );
void write_friendApply_unread( char * name );
int count_friendApply_result();

int Cur_class;                  //当前操作类型（群组/私聊）
int Cur_state;                  //当前状态：0 非聊天状态，1 聊天状态
char Cur_name[MAX_NAME_SIZE];   //当前聊天对象

msgNode * Head;
int apply_num = 0;              //好友申请数目 
int apply_result = 0;           //申请回复数
int unread_cnt = 0;             //未读信息总数
int sockfd;                     //套接字符号
int FLAG[10];                   //发出的任务完成状态,初始-1，1成功，0失败。
int My_ID = 0;                  //当前登录用户的id
char My_Name[MAX_NAME_SIZE];    //当前登录的用户名

int ID_buf;
char type_buf[5];
char name_buf[MAX_NAME_SIZE];
char msg_buf[MAX_MESSAGE_BUF];
char buffer[MAXSIZE];

#include"friend.c"
#include"unread.c"
#include"message.c"
#include"form.c"


int main( void )
{
    pthread_t thid;
    struct sockaddr_in serv_addr;
    char buf[MAXSIZE];
    int connfd , optval;
    
    Head = Read_unread();
    count_friendApply();
    count_friendApply_result();
    
    if( ( sockfd = socket( AF_INET , SOCK_STREAM , 0 ) ) < 0 ){
        perror("socket create wrong !");
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons( PORT );
    inet_aton( HOST_ADDR , &serv_addr.sin_addr );
    printf("connecting……\n");
    if(connect( sockfd , ( struct sockaddr * )&serv_addr , sizeof( struct sockaddr_in ) )){
        perror("connect failed.");
        exit(1);
    }else{
        printf("has connected...\n");
    }
    if( pthread_create( &thid , NULL , (void *)&Start_form , NULL ) != 0 ){
        perror( "thread create failed." );
        exit(1);
    }
    while( 1 ){
        recv( sockfd , buf , MAXSIZE , 0 );
//        printf("buf = %s\n",buf);
        process_msg( buf );
    }
    return 0;
}

