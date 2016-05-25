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

int Friend_apply( char * name )
{//当好友申请发送过来时，调用此函数，同意返回1,不同意返回0
    char c;
    
    while(1){
        printf("[ 系统提示 ]：%s想要勾搭，咳,加你为好友，你的态度？[Y]同意  [N]拒绝\n",name);
        scanf("%c",&c);
        if( c == 'y' || c == 'Y' ){
            Add_friend( name , USR_CLASS )
            return 1;
        }else if( c == 'n' || c == 'N' ){
            return 0;
        }else{
            printf("[ 系统提示 ]请给一个明确的态度，你这样我会很为难的QAQ～\n");
        }
    }
}




