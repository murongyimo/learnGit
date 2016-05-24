/*************************************************************************
	> File Name: message.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月12日 星期四 22时11分57秒
 ************************************************************************/


void Read_msgRecord( char * name  , int message_class )
{
    //读取聊天记录文件
    //以message_class标记为群消息记录或者私聊消息记录
    int fd , len;
    char path[MAXPATH],msg_buf[MAX_MESSAGE_BUF] ;
    path[0] = '\0';
    if( message_class == GRP_CLASS ){
        strcat( path , "./MsgRead/grp/\0" );
    }else{
        strcat( path , "./MsgRead/usr/\0" );
    }
    strcat( path , name );
    if( (fd = open( path , O_RDONLY ) ) == -1)
    {
        perror("open path wrong!");
        exit(1);
    }else{

        printf("×××××××××××××××[%s]的消息记录×××××××××××××××\n",name);
        lseek( fd , 0 , SEEK_END);
        len = lseek( fd , 0 , SEEK_CUR ) ;
        lseek( fd , 0 , SEEK_SET );
        while( len >= MAX_MESSAGE_BUF ){
            read( fd , (void *)(msg_buf) , MAX_MESSAGE_BUF-1 );
            msg_buf[MAX_MESSAGE_BUF - 1] = '\0';
            printf("%s",msg_buf);
            len =len - MAX_MESSAGE_BUF + 1;
        }
        read( fd , (void *)(msg_buf) , len );
        msg_buf[len] = '\0';
        printf("%s",msg_buf);
        close(fd);
        printf("\n×××××××××××××××打印结束×××××××××××××××\n");        

    }
}
void Write_msgRecord( char * name ,char * msg_name , char * msg , char * time , int message_class )
{
    //向文件中写入文件记录
    //[~发言人~]时间\n
    // \t>>聊天内容\n
    int fd;
    char path[MAXPATH],msg_buf[MAX_MESSAGE_BUF];
    if( Is_Friend( name ,message_class ) ){
        path[0] = '\0';
        msg_buf[0] = '\0';
        if( message_class == GRP_CLASS ){
            strcat( path , "./MsgRead/grp/\0" );
        }else{
            strcat( path , "./MsgRead/usr/\0" );
        }
        strcat( path , name );
        if( (fd = open( path , O_WRONLY|O_APPEND ) ) == -1)
        {
            perror("open path wrong!");
            exit(1);
        }else{
            strcat( msg_buf , "[~\0" );
            strcat( msg_buf , msg_name );
            strcat( msg_buf , "~]\t\0" );
            strcat( msg_buf , time );
            strcat( msg_buf , "\n\0" );
            write( fd , ( void * )msg_buf ,strlen( msg_buf ) );
            strcpy( msg_buf , ">> \0" );
            strcat( msg_buf , msg );
            strcat( msg_buf , "\n\0" );
            write( fd , ( void * )msg_buf , strlen( msg_buf ) );
            close( fd );
        }
    }
}

void Print_msgDir( int message_class )
{//打印好友列表
    DIR * fd_usr , * fd_grp ;
    int i = 1;
    struct dirent * filename;
    if( message_class == USR_CLASS ){
        fd_usr = opendir( "./MsgRead/usr/" );

        printf("×××××××××××××××私聊列表×××××××××××××××\n");
        do{
            filename = readdir( fd_usr );
            if(filename && strcmp(filename->d_name , ".") && strcmp( filename->d_name , ".." )){
                printf("\t%d. %s\n",i++ ,filename->d_name);
            }
        }while( filename );
        closedir( fd_usr );
        printf("\n×××××××××××××××××××××××××××××××××××××\n");
    }else if( message_class == GRP_CLASS ){
        fd_grp = opendir( "./MsgRead/grp/" );
        printf("×××××××××××××××群聊列表×××××××××××××××\n");

        do{
            filename = readdir( fd_grp );
            if(filename && strcmp(filename->d_name , ".") && strcmp( filename->d_name , ".." ))
                printf("\t%d. %s\n",i++ ,filename->d_name);
        }while( filename );
        closedir( fd_grp );
        printf("\n×××××××××××××××××××××××××××××××××××××\n");
    }
}

/*以上内容皆为对于消息记录的处理，下面定义关于接受服务器的消息时需要调用的函数*/

void Cut_msg( char * buf , char * name , char * type , char * msg )
{//分割服务器发过来的信息
    strcpy( name , strtok( buf , "#" ) );
    strcpy( type , strtok( NULL , "#" ) );
    strcpy( msg , strtok( NULL , "\n" ) );
}

void get_Time( char * now_time )
{//获得当前时间
    time_t t;
    t = time(NULL);
    strcpy( now_time , ctime( &t ) );
}

void process_msg( char * buf )
{//处理从服务器接受的信息的主函数
    char name[MAX_NAME_SIZE] , type[5] , msg[MAX_MESSAGE_BUF] , * Grp_name , * Grp_msg, now_time[MAX_TIME_SIZE];
    get_Time(now_time);
    Cut_msg( buf , name , type , msg );
    switch( type[0] ){
        case '0':{
            if( msg[0] == '0' )
                FLAG[0] = 0;
            else{
                FLAG[0] = 1;
                My_ID = atoi( msg );
            }
            break;
        }
        case '1':{
            if( msg[1] == '0' )
                FLAG[1] = 0;
            else{
                FLAG[1] = 1;
            }            
            break;
        }
        case '2':{
            if( msg[2] == '0' )
                FLAG[2] = 0;
            else{
                Add_friend( name , USR_CLASS );                
                FLAG[2] = 1;
            }     
            break;
        }
        case '3':{
             if( msg[3] == '0' )
                FLAG[3] = 0;
            else{
                Del_friend( name , USR_CLASS );                
                FLAG[3] = 1;
            }                
            break;
        }
        case '4':{
            if( msg[4] == '0' )
                FLAG[4] = 0;
            else{
                Add_friend( name , GRP_CLASS );                
                FLAG[4] = 1;
            }                 
            break;
        }
        case '5':{
            if( msg[5] == '0' )
                FLAG[5] = 0;
            else{
                Add_friend( name , GRP_CLASS );                
                FLAG[5] = 1;
            }           
            break;
        }
        case '6':{
            if( msg[6] == '0' )
                FLAG[6] = 0;
            else{
                Del_friend( name , GRP_CLASS );                
                FLAG[6] = 1;
            }              
            break;
        }
        case '7':{
            if( Cur_state == 1 && Cur_class == USR_CLASS && !strcmp( name , Cur_name ) ){
                printf("[%s 说：]%s\n",name,msg);
                Write_msgRecord( name , name , msg , now_time , USR_CLASS );
            }else{
                MsgIn_unread( Head , 1 , USR_CLASS , name );
                Write_msgRecord( name , name , msg , now_time , USR_CLASS );
            }
            break;
        }
        case '8':{
            //当前操作为群时，name为群名，Grp_name 为发送用户名,Grp_msg 为消息。
            Grp_name = strtok( msg , "#" );
            Grp_msg = strtok( NULL , "\n" );
            if( Cur_state == 1 && Cur_class == GRP_CLASS && !strcmp( name , Cur_name ) ){
                printf("[%s 说：]%s\n",Grp_name,Grp_msg);
                Write_msgRecord( name , Grp_name , Grp_msg , now_time , GRP_CLASS );
            }else{
                MsgIn_unread( Head , 1 , GRP_CLASS , name );
                Write_msgRecord( name , Grp_name , Grp_msg , now_time , GRP_CLASS );
            }
            break;
        }
        case '9':{
            if( msg[9] == '0' )
                FLAG[9] = 0;
            else               
                FLAG[9] = 1;            
            break;
        }

    }
}

/*以下内容为客户端将信息组合发送出去的函数*/

void Comb_msg( char * buf , char * type,char * name  , char * msg )
{//组合即将发送的信息
    if( type[0] == '8' )
        sprintf( buf , "%d#%s#%s#%s#%s\n" , My_ID,type,name,My_Name,msg );
    else
        sprintf( buf , "%d#%s#%s#%s\n" , My_ID,type,name,msg );
}












