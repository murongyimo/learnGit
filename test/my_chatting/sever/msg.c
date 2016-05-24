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

void Recv_msg( int * connfd )
{//收到客户端的信息，并进行处理   (waiting~)
    char buf[MAXSIZE] , type[5] , msg[MAX_MESSAGE_BUF] , name[MAX_NAME_SIZE] ;
    int id;
    recv( *connfd , &buf , MAXSIZE , 0 );
    Cut_msg( buf , &id , type , name , msg );
    
    switch(type[0]){
        case '0':{
            break;
        }
        case '1':{
            break;
        }
        case '2':{
            break;
        }
        case '3':{
            break;
        }
        case '4':{
            break;
        }
        case '5':{
            break;
        }
        case '6':{
            break;
        }
        case '7':{
            break;
        }
        case '8':{
            break;
        }
        case '9':{
            break;
        }
    }


}
