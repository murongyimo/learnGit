/*************************************************************************
	> File Name: Usr.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月22日 星期日 09时59分54秒
 ************************************************************************/



int Is_usr( char * name )
{//检测用户名是否存在,若存在返回id，不存在返回0
    int id = 0 , ID;
    char buf[MAX_NAME_SIZE + MAX_PASSWD_SIZE + 10] , name_buf[MAX_NAME_SIZE] , passwd[MAX_PASSWD_SIZE];
    FILE * fd;
    if(  !( fd = fopen( "passwd.txt" ,  "r"  ) )){
        perror( "open passwd.txt wrong !" );
        exit(1);
    }else{
        while( 3 == fscanf( fd , "%s %s %d\n" , name_buf , passwd , &ID ) ){
            if( !strcmp( name , name_buf ) ){
                id = ID;
                break;
            }
        }   
        fclose(fd);
    }
    return id;
}

int Is_online( char * name )
{//检测用户是否在线，在线返回0，不存在返回1,不在线返回2
    int id = Is_usr(name);
    if( !id )
        return 1;
    else if(USR[id].state == 1)
        return 0;
    else
        return 2;
}

int Add_usr( char * name , char * passwd )
{//注册，使用函数之前先检验用户是否存在，不存在调用，成功返回id，不成功返回0,格式：用户名 密码 id\n
    int fd , id = 0;
    char buf[MAX_NAME_SIZE + MAX_PASSWD_SIZE + 10];
    if( ( fd = open( "passwd.txt" , O_WRONLY|O_APPEND ) ) == -1){
        perror( "open passwd.txt wrong !" );
        exit(1);        
    }else{
        id = Get_usr_num() + 1;
        Chg_usr_num(id);
        sprintf( buf , "%s %s %d\n", name , passwd , id );
        write( fd , buf , strlen(buf) );
        close(fd);
        strcpy(USR[id].name , name);
        USR[id].state = 0;
    }
    return id;
}

int Check_usr( char * name , char * passwd )
{//验证用户名与密码是否匹配，匹配返回0，不匹配返回1
    int ID;
    char buf[MAX_NAME_SIZE + MAX_PASSWD_SIZE + 10] , name_buf[MAX_NAME_SIZE] , passwd_buf[MAX_PASSWD_SIZE];
    FILE * fd;
    if(  !( fd = fopen( "passwd.txt" ,  "r"  ) )){
        perror( "open passwd.txt wrong !" );
        exit(1);
    }else{
        while( 3 == fscanf( fd , "%s %s %d\n" , name_buf , passwd_buf , &ID ) ){
            if( !strcmp( name , name_buf ) ){
                break;
            }
        }   
        fclose(fd);
    }
    if( !strcmp( passwd , passwd_buf) )
        return 0;
    else
        return 1;
}

void Chg_usr_num( int num )
{//修改用户总数为num
    int fd;
    char buf[10];
    sprintf( buf , "%d" , num );
 if( ( fd = open( "usr_num.txt" , O_WRONLY|O_TRUNC ) ) == -1){
        perror( "open usr_num.txt wrong !" );
        exit(1);        
    }else{
        write( fd , buf , strlen(buf) );
        close(fd);
    }    
}

int Get_usr_num()
{//获得用户总数
    int fd;
    char buf[10];
    int num;
    if( ( fd = open( "usr_num.txt" , O_RDONLY ) ) == -1 ){
        perror( "open usr_num.txt wrong !" );
        exit(1);        
    }else{
        if( read( fd , buf , sizeof(buf) ) )
            num = atoi(buf);
        else
            num = 0;
        close(fd);
    }    
    return num;
}

void get_Time( char * now_time )
{//获得当前时间
    time_t t;
    t = time(NULL);
    strcpy( now_time , ctime( &t ) );
}

void Log_write( int id , char * name , int cls )
{//写入日志：cls = 0为登录，cls = 1为注销
    char time[MAX_TIME_SIZE] , state[20],buf[MAX_TIME_SIZE+50+MAX_NAME_SIZE];
    int fd;
    get_Time(time);
    if(cls == 0)
        strcpy(state , "Log in.\n");
    else
        strcpy(state , "Log out.\n");
    sprintf( buf , "%d %s %s %s\n",id , name , state , time );
    
    if( ( fd = open( "log.txt" , O_WRONLY|O_APPEND ) ) == -1){
        perror( "open log.txt wrong !" );
        exit(1);        
    }else{
        write( fd , buf , strlen(buf) );
        close(fd);
    }        
}

int LogIn_usr( char * name , char * passwd )
{//用户登录，成功返回id，不成功返回0
    int id = 0 , ID;
    char buf[MAX_NAME_SIZE + MAX_PASSWD_SIZE + 10] , name_buf[MAX_NAME_SIZE] , passwd_buf[MAX_PASSWD_SIZE];
    FILE * fd;
    if(  !( fd = fopen( "passwd.txt" ,  "r"  ) )){
        perror( "open passwd.txt wrong !" );
        exit(1);
    }else{
        while( 3 == fscanf( fd , "%s %s %d\n" , name_buf , passwd , &ID ) ){
            if( !strcmp( name , name_buf ) ){
                break;
            }
        }   
        fclose(fd);
        if(!strcmp(passwd_buf,passwd)){
            id = ID;
            USR[id].state = 1;
            Log_write( id , name , 0 );
        }
    }
    return id;    
}

void Log_Out_usr( int id )
{//用户注销
    USR[id].state = 0;
    Log_write( id , USR[id].name , 1 );
    free(USR[id].connfd);
}
