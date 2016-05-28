/*************************************************************************
	> File Name: unread.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月13日 星期五 22时56分50秒
 ************************************************************************/



msgNode * Init_unread()
{//初始化未读信息节点
    msgNode * h;
    h = ( msgNode * )malloc( sizeof( msgNode ) );
    h->next = NULL;
    return h;
}

void ADD_unread( msgNode * h , msgNode * s )
{//增加未读信息节点,若用户名和类型都已经存入，则cnt相加，不进行加入。
    msgNode * p = h -> next ;
    while( p ){
        if( !strcmp( p -> name , s -> name ) && p ->type == s ->type )
            break;
        p = p->next;
    }
    if( p ){
        p->cnt += s->cnt;
        free( s );
    }else{
        p = h -> next ;
        h->next = s;
        s->next = p;
    }
}

void Del_unread( msgNode * h , msgNode * p )
{//删除p指向的未读信息节点
    while( h->next != p ){
        h = h->next ;
    }
    h->next = p->next;
    free(p);
}

msgNode * Find_unread( msgNode * h , char * name , int type )
{//查找姓名为name,类型为Type的节点，找到返回指针，未找到返回NULL 
    msgNode * p = h->next;
    while(p){
        if( !strcmp( p->name , name ) && p->type == type )
            break;
        else 
            p = p->next;
    }
    return p;
}

void Delete_list( msgNode * h )
{//释放链表
    msgNode * p, * q;
    p = h->next;
    while(p){
        q = p;
        p = p->next;
        h -> next = p;
        free(q);
    }
}

msgNode * Create_unreadNode( int cnt , int type ,char * name )
{//建立未读信息节点
    msgNode * p = ( msgNode * )malloc( sizeof(msgNode) );
    p->cnt = cnt ;
    p->type = type ;
    strcpy( p->name , name );
    p->next = NULL;
    return p ;
}

void Write_unread( msgNode * h )
{//向文件中写入链表中的内容，格式：类型#用户（组）名#条数#\n
    char unread_buf[UNREAD] , cnt[10];
    int fd , len;
    msgNode * p = h ->next ; 
    if( ( fd = open( "./MsgRead/unread" , O_WRONLY|O_TRUNC ) ) == -1){
        perror( "open unread wrong !" );
        exit(1);
    }else{
        while( p ){
            sprintf( unread_buf , "%d#%s#%d\n" , p->type , p->name , p->cnt);
            p = p->next;
            write( fd , unread_buf , strlen(unread_buf) );
        }
        close( fd );
    }
}

msgNode * Read_unread()
{//读取文件中内容，创建链表。
    msgNode * h , *p;
    FILE * fd;
    char unread_buf[UNREAD] ,* s , * name ;
    int type , cnt ;
    memset( unread_buf , 0 ,sizeof(unread_buf) );
    h = Init_unread();
    if( !( fd = fopen( "./MsgRead/unread" ,  "r"  ) ) ){
        perror("unread open error");
        exit(1);
    }else{
        while( 1 ){
            if(!(fgets( unread_buf , UNREAD , fd )))
                break;
            if( !( s = strtok( unread_buf , "#" ) ) ){
                perror("getting type error");
                exit(1);
            }else{
                type = atoi( s );
                if( !( name = strtok( NULL , "#" ) ) ){
                    perror("getting name error");
                    exit(1);
                }else{
                    if( !( s = strtok( NULL , "\n" ) ) ){
                        perror("getting name error");
                        exit(1);
                    }else{
                        cnt = atoi( s );
                        p = Create_unreadNode( cnt , type , name );
                        ADD_unread( h , p );
                    }
                }
            }
        }
        fclose(fd);
        unread_cnt = Get_unread_cnt( h );
        return h;
    }
}

void Print_unread( msgNode * h )
 {//打印未读信息链表
     msgNode * p= h -> next;
     int i = 1;
     printf("\t\t\t×××××未读信息列表×××××\n");
     printf("\t编号\t类型i\t ---\t用户（组）名\t\t未读信息数\n\n");
     while( p ){
         if( p -> type == USR_CLASS )
            printf("\t %d. \t USR_CLASS\t ---\t%s\t\t%d\n ",i++,p->name,p->cnt);
         else
            printf("\t %d. \t GRP_CLASS\t ---\t%s\t\t%d\n",i++,p->name,p->cnt);
         p = p ->next;
     }
     printf("\t\t\t  ×××××打印结束×××××\n\n");
 }

int Check_unread( msgNode * h ,char * name , int type )
{//查看聊天记录，删除名称为name，类型为type的节点，没有返回-1
    msgNode * p = h->next ;
    while( p ){
        if( !strcmp( name , p -> name ) && p->type == type )
            break;
        p = p -> next;
    }
    if( p ){
        Read_msgRecord( name  , type );        
        Del_unread( h , p );
        Write_unread( Head );
        return 0;
    }else
        return -1;
}

void MsgIn_unread( msgNode * h , int cnt , int type , char * name )
{//收到消息后，将内容存储到未读信息链表及文件中
    msgNode * p ;
    p = Create_unreadNode( cnt , type , name );
    ADD_unread( h , p );
    unread_cnt = Get_unread_cnt( h );
    Write_unread( h );
}

void Clear_unread( msgNode * h )
{//清空未读信息列表
    Delete_list( h );
    Write_unread( h );
}

int Get_unread_cnt( msgNode * h )
{//返回未读信息总数
    int cnt = 0;
    msgNode * p = h -> next;
    while(p){
        cnt += p -> cnt;
        p = p->next;
    }
    return cnt;
}
