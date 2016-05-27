/*************************************************************************
	> File Name: friend.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月15日 星期日 10时14分41秒
 ************************************************************************/

int Is_Friend( char * name , int type )
{//判断是否存在于好友列表当中,是好友返回1,不是返回0
    DIR * fd ;
    struct dirent * filename; 

    if( type == USR_CLASS ){
        fd = opendir( "./MsgRead/usr/" );  
        do{
            filename = readdir( fd );
            if(filename && !strcmp( filename ->d_name , name)){
                break;
            }
        }while( filename );
        closedir( fd );
    }else if( type == GRP_CLASS ){
        fd = opendir( "./MsgRead/grp/" ); 
        do{
            filename = readdir( fd );
            if(filename && !strcmp( filename ->d_name , name)){
                break;
            }
        }while( filename );
        closedir( fd );        
    }else{
        return -1;
    }
    if( filename )
        return 1;
    else
        return 0;
}

int Add_friend( char * name , int type )
{//添加好友，如果已经在好友列表里则直接返回，如果不在好友列表则加入好友列表，返回1
    int fd ;
    char path[MAXPATH];    
    if( Is_Friend( name ,type ) ){
        printf("[ 系统提示 ] Ta 已经是你的好友了!\n");
        return 0;
    }else{
        path[0] = '\0';
        if( type == GRP_CLASS ){
            strcat( path , "./MsgRead/grp/\0" );
        }else{
            strcat( path , "./MsgRead/usr/\0" );
        }
        strcat( path , name );
        if(creat( path , S_IRUSR|S_IWUSR ) == -1 ){
            perror("there is some wrong with Add_friend.");
            exit(1);
        }else{
            printf("[ 系统提示 ] 好友“%s”加入成功～你们可以开始无节操的玩耍啦(^_^)/~\n",name);
            return 1;
        }
    }
}

int Del_friend( char * name , int type )
{//删除好友，删除成功返回1，否则返回0
    char path[MAXPATH];  
    if( Is_Friend( name ,type ) ){
        path[0] = '\0';
        if( type == GRP_CLASS ){
            strcat( path , "./MsgRead/grp/\0" );
        }else{
            strcat( path , "./MsgRead/usr/\0" );
        }
        strcat( path , name );
        if(remove( path ) == -1 ){
            perror("there is some wrong with Del_friend.");
            exit(1);
        }else{
            printf("[ 系统提示 ] 好友“%s”删除成功\n",name);
            return 1;
        }       
    }else{
        return 0;
    }
}

int count_friendApply()
{//用于初始化未处理的好友申请数目
    FILE * fd ;
    char name[MAX_NAME_SIZE];
    if(  !( fd = fopen( "./apply/friend_apply" ,  "r"  ) )){
        perror( "open ./apply/friend_apply wrong !" );
        exit(1);
    }else{
        while( 1 == fscanf( fd , "%s\n" , name ) ){
            apply_num++;
        }   
        fclose(fd);
    }  
}

int count_friendApply_result()
{//用于初始化未查看的申请回复数目
    FILE * fd ;
    char name[MAX_NAME_SIZE] , buf[MAX_NAME_SIZE + 100];
    if(  !( fd = fopen( "./apply/apply_result" ,  "r"  ) )){
        perror( "open ./apply/apply_result wrong !" );
        exit(1);
    }else{
        while(fgets( buf , sizeof(buf) , fd ) ){
            apply_result++;
        }   
        fclose(fd);
    }  
}

int Friend_apply( char * name )
{//当好友申请发送过来时，调用此函数，同意返回1,不同意返回0
    char c , c1;
    
    while(1){
        printf("[ 系统提示 ]：%s想要勾搭，咳,加你为好友，你的态度？[Y]同意  [N]拒绝\n",name);
        scanf("%c",&c);
        while( ( c1 = getchar() ) != '\n' && c1 != EOF );
        if( c == 'y' || c == 'Y' ){
            Add_friend( name , USR_CLASS );
            return 1;
        }else if( c == 'n' || c == 'N' ){
            return 0;
        }else{
            printf("[ 系统提示 ]请给一个明确的态度，你这样我会很为难的QAQ～\n");
        }
    }
}

void watch_friendApply()
{//查看发出的好友申请的处理结果
    FILE * fd ;
    int result , clfd;
    char buf[MAX_NAME_SIZE + 100];
    if(  !( fd = fopen( "./apply/apply_result" ,  "r"  ) )){
        perror( "open ./apply/apply_result wrong !" );
        exit(1);
    }else{
        while( fgets( buf , sizeof(buf) , fd ) ){
            printf("%s\n",buf);
        }   
        fclose(fd);
    }  
    if( ( clfd = open( "./apply/apply_result" , O_WRONLY|O_TRUNC ) ) == -1){
        perror( "open ./apply/friend_apply wrong !" );
        exit(1);        
    }else{
        close(clfd);
        apply_result = 0;
    }
}

void handle_friendApply()
{//处理服务器发送过来的好友申请
    FILE * fd ;
    int result , clfd;
    char name[MAX_NAME_SIZE] , buf[MAXSIZE];
    if(  !( fd = fopen( "./apply/friend_apply" ,  "r"  ) )){
        perror( "open ./apply/friend_apply wrong !" );
        exit(1);
    }else{
        while( 1 == fscanf( fd , "%s\n" , name ) ){
            result = Friend_apply( name );
            if( result == 1 )
                Comb_msg( buf , "2" , name , "1" );//同意
            else
                Comb_msg( buf , "2" , name, "2" );//拒绝
            send( sockfd , buf , MAXSIZE , 0 );
        }   
        fclose(fd);
    }  
    if( ( clfd = open( "./apply/friend_apply" , O_WRONLY|O_TRUNC ) ) == -1){
        perror( "open ./apply/friend_apply wrong !" );
        exit(1);        
    }else{
        close(clfd);
        apply_num = 0;
    }

}


void write_friendApply_result( char * name , int type )
{//用于向apply_result文件中写入 发出的好友申请 的 处理结果。type为1同意，为0拒绝。 
    int fd ;
    char buf[MAX_NAME_SIZE + 100];
    if( ( fd = open( "./apply/apply_result" , O_WRONLY|O_APPEND ) ) == -1){
        perror( "open ./apply/apply_result wrong !" );
        exit(1);        
    }else{
        if( type == 0 )
            sprintf( buf , "%s 拒绝了你的好友申请～魅力值不够呀，亲～\n", name );
        else
            sprintf( buf , "%s 批准了你申请发展纯洁革命友谊的请求，和好基友一起愉快的玩耍吧～\n", name );
        write( fd , buf , strlen(buf) );
        close(fd);
        apply_result++;
    }
}

void write_friendApply_unread( char * name )
{//用于向文件friend_apply中写入 服务器发送的好友申请，等待处理。
    int fd ;
    char buf[MAX_NAME_SIZE];
    if( ( fd = open( "./apply/friend_apply" , O_WRONLY|O_APPEND ) ) == -1){
        perror( "open ./apply/friend_apply wrong !" );
        exit(1);        
    }else{
        sprintf( buf , "%s\n", name );
        write( fd , buf , strlen(buf) );
        close(fd);
        apply_num++;   
    }   

}

