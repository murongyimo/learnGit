/*************************************************************************
	> File Name: group.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月22日 星期日 19时21分25秒
 ************************************************************************/


/*在一个群中，最大人数为MAX_GRP_USR
 * 群文件中，格式为：总人数n 用户id1 用户id2 用户id3……用户idn
 */

int Is_Grp( char * grp_name )
{//查找群名是否存在，存在返回0,不存在返回1
    DIR * fd ;
    struct dirent * filename; 
    fd = opendir( "./Grp/" );  
    do{
        filename = readdir( fd );
        if(filename && !strcmp( filename ->d_name , grp_name)){
            break;
        }
    }while( filename );
        closedir( fd ); 
    if( filename )
        return 0;
    else
        return 1;
}

int Create_Grp( char * grp_name , int id )
{//新建群，成功返回0,失败(群名已存在)返回1
    char path[MAXPATH] , buf[10];
    int fd;
    if(!Is_Grp(grp_name))
        return 1;
    else{
        strcpy( path , "./Grp/\0" );
        strcat( path , grp_name );
        if(creat( path , S_IRUSR|S_IWUSR ) == -1 ){
            perror("there is some wrong with Create_Grp.");
            exit(1);
        }else{
            if( ( fd = open( path , O_WRONLY|O_TRUNC ) ) == -1){
                    perror( "open usr_num.txt wrong !" );
                    exit(1);        
                }else{
                    sprintf( buf , "1 %d" , id );
                    write( fd , buf , strlen(buf) );
                    close(fd);
                    return 0;
                }             
        }
    }
}

int Join_Grp( char * grp_name , int id )
{//加入群，成功返回0，失败(群不存在)返回1,人数以达到最大返回2,已经在群内返回3
    char path[MAXPATH];
    FILE * fd;
    int num , i , ID[MAX_GRP_USR];
    if( Is_Grp( grp_name ) )
        return 1;
    else{
        strcpy( path , "./Grp/\0" );
        strcat( path , grp_name );
        if(  !( fd = fopen(  path ,  "r"  ) )){
            perror( "open grp_name wrong !" );
            exit(1);
        }else{
            fscanf( fd , "%d" , &num );
            if( num >= MAX_GRP_USR ){
                fclose(fd);
                return 2;
            }
            else{
                for( i = 0 ; i < num ; i++)
                    fscanf( fd , " %d" , ID+i );
                fclose(fd);
                if(  !( fd = fopen(  path ,  "w"  ) )){
                    perror( "open grp_name wrong !" );
                    exit(1);
                }else{            
                    fprintf( fd , "%d" , num+1 );
                    for( i = 0 ; i < num ; i++){
                        if( ID[i] == id )
                            return 3;
                        else
                            fprintf( fd , " %d" , ID[i] );
                    }
                    fprintf( fd , " %d" , id );
                    fclose(fd);
                    return 0;
                }
            }
        }
    }
}

void Exit_Grp( char * grp_name , int id )
{//退出群
    char path[MAXPATH];
    FILE * fd;
    int num , i , ID[MAX_GRP_USR];
    strcpy( path , "./Grp/\0" );
    strcat( path , grp_name );
    if(  !( fd = fopen(  path ,  "r"  ) )){
        perror( "open grp_name wrong !" );
        exit(1);
    }else{
            fscanf( fd , "%d" , &num );
            for( i = 0 ; i < num ; i++)
                fscanf( fd , " %d" , ID+i );
            fclose(fd);
            if(  !( fd = fopen(  path ,  "w"  ) )){
                perror( "open grp_name wrong !" );
                exit(1);
            }else{            
                fprintf( fd , "%d" , num-1 );
                for( i = 0 ; i < num ; i++){
                    if( ID[i] == id )
                        continue;
                    else
                        fprintf( fd , " %d" , ID[i] );
                }
                fclose(fd);
            }
    }    
}

