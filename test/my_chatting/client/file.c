/*************************************************************************
	> File Name: mkfile.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月11日 星期三 19时16分51秒
 ************************************************************************/

void create_file()
{
    int fd1,fd2;
    if(  mkdir( "./MsgRead" , S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP ) == -1)
    {
        perror("Created directorty MsgRead  wrong!");
        exit(1);
    }
    if(  mkdir( "./MsgRead/usr" , S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP ) == -1)
    {
        perror("Created directorty usr wrong!");
        exit(1);
    }
    if(  mkdir( "apply" , S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP ) == -1)
    {
        perror("Created directorty apply  wrong!");
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
    if( (fd1 = creat( "./apply/friend_apply" ,  S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP ) ) == -1)
    {
        perror("Created passwd.txt wrong!");
        exit(1);
    }
    if( (fd1 = creat( "./apply/apply_result" ,  S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP ) ) == -1)
    {
        perror("Created passwd.txt wrong!");
        exit(1);
    }
}

int Is_usr( char * name )
{//核对姓名为name的用户是否在USR文件夹中，存在返回1 ，不存在返回0
    DIR * fd ;
    struct dirent * filename; 
    fd = opendir( "./USR/" );  
    do{
        filename = readdir( fd );
        if(filename && !strcmp( filename ->d_name , name)){
            break;
        }
    }while( filename );
    closedir( fd );
    if( filename )
        return 1;
    else
        return 0;
}

void chg_dir( char * name )
{//切换工作目录，从./main所在目录进入USR中name对应的用户文件夹
    char path[MAXPATH];
    if( !( Is_usr( name ) ) ){
        sprintf( path , "./USR/%s" , name );
        printf("path = %s\n",path);
    if(  mkdir( path , S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP ) == -1)
    {
        perror("Created directorty usrname wrong!");
        exit(1);
    }    
    chdir("./USR");
    chdir(name);  
    create_file();
    }else{
        chdir("./USR");
        chdir(name);
        printf("there must be wrong.\n");
    }
}





