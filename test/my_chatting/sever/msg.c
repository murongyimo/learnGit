/*************************************************************************
	> File Name: msg.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月22日 星期日 00时18分10秒
 ************************************************************************/


void Cut_msg( char * buf , int * id , char * type , char * name , char * msg )
{//分割服务器发过来的信息
    char * ID;
    ID = strtok( buf , "#" );
    *id = atoi(ID);
    strcpy( name , strtok( buf , "#" ) );
    strcpy( type , strtok( NULL , "#" ) );
    strcpy( msg , strtok( NULL , "\n" ) );
}

void Conbine_msg( char * buf , char * name , char * type , char * msg )
{//组合待发送的信息(格式)：发送者姓名#类型#消息内容\n
    sprintf( buf , "%s#%s#%s\n" , name , type , msg );
}

void Recv_msg( int * connfd )
{   //收到客户端的信息，并进行处理   (waiting~)
    //name:发送者姓名
    char buf[MAXSIZE] , type[5] , msg[MAX_MESSAGE_BUF] , name[MAX_NAME_SIZE] , id_buf[5];
    int id , i , fd = *connfd;//发送者的socket
    recv( *connfd , &buf , MAXSIZE , 0 );
    Cut_msg( buf , &id , type , name , msg );
    sprintf( id_buf , "%d" , id );
    switch(type[0]){
        case '0':{
            if( strcmp( name , "$" ) ){//用户名检验
                if( Is_usr( msg ) )
                    Conbine_msg( buf , "$" , "0" , "0" );//用户不存在
                else
                    Conbine_msg( buf , "$" , "0" , id_buf );//用户存在 
            }else{//密码校验
                if( Check_usr( name , msg ) )
                    Conbine_msg( buf , "$" , "0" , "0" );//用户登录失败
                else{
                    LogIn_usr( name , msg );
                    Conbine_msg( buf , "$" , "0" , id_buf );//用户登录成功
                }
            }
            break;
        }
        case '1':{
            if( strcmp( name , "$" ) ){//用户名检验
                if( Is_usr( msg ) )
                    Conbine_msg( buf , "$" , "1" , "0" );//用户不存在
                else
                    Conbine_msg( buf , "$" , "1" , id_buf );//用户存在 
            }else{
                if( !Add_usr( name , msg ) )
                    Conbine_msg( buf , "$" , "1" , "0" );//用户注册失败
                else
                    Conbine_msg( buf , "$" , "1" , id_buf );//用户注册成功
            }            
            break;
        }
        case '2':{

            if( msg[0] == '0' ){
                i = Is_online( name );               
                if( i == 1 )
                    Conbine_msg( buf , "$" , "2" , "3" );
                else if( i == 2 )
                    Conbine_msg( buf , "$" , "2" , "4" );
                else{
                    Conbine_msg( buf , USR[id].name , "2" , "2" );
                    id = Is_usr( name );
                    fd = * ( USR[id].fd );
                }
            }else if( msg[0] == '1' ){
                Conbine_msg( buf , USR[id].name , "2" , "1" );
                id = Is_usr( name );                
                fd = * ( USR[id].fd );
            }else if( msg[1] == '2' ){
                Conbine_msg( buf , USR[id].name , "2" , "0" );
                id = Is_usr( name );                
                fd = * ( USR[id].fd );
            }
            break;
        }
        case '3':{
            if( Is_online( name ) == 2 ){
                Conbine_msg( buf , "$" , "3" , "0" );
            }else{
                if( msg[0] == '0' ){
                    Conbine_msg( buf , USR[id].name , "3" , "1" );
                }else if( msg[0] == '1' ){
                    Conbine_msg( buf , USR[id].name , "3" , "2" );
                }
                id = Is_usr( name );                
                fd = * ( USR[id].fd );                    
            }
            break;
        }
        case '4':{
            if( !Is_Grp( name ) )
                Conbine_msg( buf , "$" , "4" , "0" );
            else{
                Create_Grp( name , id );
                Conbine_msg( buf , "$" , "4" , "1" );
            }
            break;
        }
        case '5':{
            if( Is_Grp( name ) )
                Conbine_msg( buf , "$" , "5" , "3" );
            else{
                i = Join_Grp( name , id );
                if( i == 2 )
                    Conbine_msg( buf , "$" , "5" , "0" );
                else if( i == 0 )
                    Conbine_msg( buf , "$" , "5" , "1" );
            }
            break;
        }
        case '6':{
            Exit_Grp( name , id ) 
            Conbine_msg( buf , "$" , "6" , "2" );
            break;
        }
        case '7':{
            
            break;
        }
        case '8':{
            
            break;
        }
        case '9':{
            Log_Out_usr( id );
            Conbine_msg( buf , "$" , "9" , "1" );
            break;
        }
    }

    send( fd , buf , MAXSIZE , 0 );
}
