/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月15日 星期日 18时50分01秒
 ************************************************************************/


void Start_form()
{//初始界面
    int i ,flag , h;
    char passwd[MAX_PASSWD_SIZE + 2] ,name[MAX_NAME_SIZE + 2] , c , buf[MAXSIZE];
    Cur_state = 0;
    while(1){
        flag = 1;

        printf("\n×××××××××××××××登陆界面×××××××××××××××\n");
        printf("     _$0_（退出）     _$1_(注册)\n");
        printf("×××××××××××××××××××××××××××××××××××××\n\n");
        while(flag){
            h = 0;
            printf("请输入用户名：");
            fgets(  name , MAX_NAME_SIZE + 2 , stdin );
            //判定输入是否正确
            for( i = 0 ; i < MAX_NAME_SIZE + 2 ; i++ ){
                if( name[i] <48 || ( name[i] > 57 && name[i] < 65 ) || ( name[i] > 90 && name[i] < 97 ) || name[i] > 122  )
                    break;
            }

            if( i == MAX_NAME_SIZE + 1){
                printf("[wrong] >> 字符串超长，请保持在%d个字符以内!\n",MAX_NAME_SIZE);
                while( ( c = getchar() ) != '\n' && c != EOF );
            }
            else if( !strcmp( name , "$0\n" ) ){
                Comb_msg( buf, "9" , "$" , "1" );
                send( sockfd , buf , MAXSIZE , 0 );
                close(sockfd);
                printf("[ 系统提示 ]退出成功！期待下次的会面呦～MUA～\n");
                exit(0);
            }
            else if( !strcmp( name , "$1\n" ) ){
                register_form();         
                h = 1;
                flag = 0;
            }
            else if( name[i] != '\n' )
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");
        
            else{ 
                //将name传到服务器上验证
                name[i] = '\0';
                FLAG[0] = -1;
                Comb_msg( buf, "0" , "$" , name );
                send( sockfd , buf , MAXSIZE , 0 );
                while(1){
                    if(FLAG[0] == 1){//当服务器检测到用户名存在时
                        flag = 0;
                        break;
                    }else if( FLAG[0] == 0){
                        printf("[ 系统提示 ]该用户名不存在！请重新输入！\n");
                        break;
                    }
                }
            
            }
        }
        if( h == 1 ) 
            continue;   
        flag = 1;
        while(flag){
            h = 0;
            printf("请输入密码：");
            fgets(  passwd , MAX_PASSWD_SIZE + 2 , stdin );
            
            for( i = 0 ; i < MAX_PASSWD_SIZE + 2 ; i++ ){
                if( passwd[i] <48 || passwd[i] > 57 && passwd[i] < 65 || passwd[i] > 90 && passwd[i] < 97 || passwd[i] > 122  )
                    break;
            }

            if(  i == MAX_PASSWD_SIZE + 1 ){
                printf("[wrong] >> 字符串超长，请保持在%d个字符以内!\n",MAX_PASSWD_SIZE);
                while( ( c = getchar() ) != '\n' && c != EOF );
            }
            else if( !strcmp( passwd , "$0\n" ) ){
                Comb_msg( buf, "9" , "$" , "1" );
                send( sockfd , buf , MAXSIZE , 0 );
                close(sockfd);
                printf("[ 系统提示 ]退出成功！期待下次的会面呦～MUA～\n");
                exit(0);
            }
            else if( !strcmp( passwd , "$1\n" ) ){
                register_form();
                h = 1;
                break;
            }
            else if( passwd[i] != '\n' )
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");

            else{
                //将passwd传到服务器上验证/
                passwd[i] = '\0';    
                FLAG[0] = -1;
                Comb_msg( buf, "0" , name , passwd );
                send( sockfd , buf , MAXSIZE , 0 );
                while(1){
                    if(FLAG[0] == 0){
                        printf("[ 系统提示 ]密码错误！请重新输入！\n");
                        break;
                    }else if( FLAG[0] == 1 ){
                        flag = 0;
                        break;
                    }
                }                

            }
        }
        if( h == 1 ) 
            continue;
        printf("[ 系统提示 ]登录成功！ \n");
        printf("×××××××××××××××××××××××××××××××××××××\n\n");
        strcpy(My_Name,name);
        chg_dir( name );
        Head = Read_unread();
        count_friendApply();
        count_friendApply_result();
        Select_form();

    }
}

 void register_form()
{//注册界面
    int i ,flag = 1 ,h;
    char passwd[MAX_PASSWD_SIZE + 2] ,name[MAX_NAME_SIZE + 2] , c , buf[MAXSIZE];
    Cur_state = 0;
    while(1){
        h = 0;
        My_ID = 0;
        printf("\n×××××××××××××××注册界面×××××××××××××××\n");
        printf("     _$0_（退出）     _$1_(登录)\n");
        printf("×××××××××××××××××××××××××××××××××××××\n\n");
        flag = 1;
        while(flag){
            h = 0;
            printf("请输入用户名：");
            fgets(  name , MAX_NAME_SIZE + 2 , stdin );
            //判定输入是否正确
            for( i = 0 ; i < MAX_NAME_SIZE + 2 ; i++ ){
                if( name[i] <48 || ( name[i] > 57 && name[i] < 65 ) || ( name[i] > 90 && name[i] < 97 ) || name[i] > 122  )
                    break;
            }

            if( i == MAX_NAME_SIZE + 1){
                printf("[wrong] >> 字符串超长，请保持在%d个字符以内!\n",MAX_NAME_SIZE);
                while( ( c = getchar() ) != '\n' && c != EOF );
            }
            else if( !strcmp( name , "$0\n" ) ){
                Comb_msg( buf, "9" , "$" , "1" );
                send( sockfd , buf , MAXSIZE , 0 );
                close(sockfd);
                printf("[ 系统提示 ]退出成功！期待下次的会面呦～MUA～\n");
                exit(0);
            }
            else if( !strcmp( name , "$1\n" ) )
                return ;         
            else if( name[i] != '\n' )
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");
        
            else{ 
                /*将name传到服务器上验证*/
                name[i] = '\0';
                FLAG[1] = -1;
                Comb_msg( buf, "1" , "$", name  );
                send( sockfd , buf , MAXSIZE , 0 );
                while(1){
                    if(FLAG[1] == 1){//当服务器检测到用户名不存在时
                        flag = 0;
                        break;
                    }else if( FLAG[1] == 0 ){
                        printf("[ 系统提示 ]该用户名已被注册，请选择其他用户名！\n");
                        h = 1;
                        break;
                    }
                }
            }
        }

        flag = 1;
        while(flag){
            h = 0;
            printf("请输入密码：");
            fgets(  passwd , MAX_PASSWD_SIZE + 2 , stdin );
            
            for( i = 0 ; i < MAX_PASSWD_SIZE + 2 ; i++ ){
                if( passwd[i] <48 || passwd[i] > 57 && passwd[i] < 65 || passwd[i] > 90 && passwd[i] < 97 || passwd[i] > 122  )
                    break;
            }

            if(  i == MAX_PASSWD_SIZE + 1 ){
                printf("[wrong] >> 字符串超长，请保持在%d个字符以内!\n",MAX_PASSWD_SIZE);
                while( ( c = getchar() ) != '\n' && c != EOF );
            }
            else if( !strcmp( passwd , "$0\n" ) ){
                Comb_msg( buf, "9" , "$" , "1" );
                send( sockfd , buf , MAXSIZE , 0 );
                close(sockfd);
                printf("[ 系统提示 ]退出成功！期待下次的会面呦～MUA～\n");
                exit(0);
            }
            else if( !strcmp( passwd , "$1\n" ) )
                return ;       
            else if( passwd[i] != '\n' )
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");

            else{
                /*将passwd传到服务器上验证*/
                passwd[i] = '\0';      
                FLAG[1] = -1;
                Comb_msg( buf, "1" , name , passwd  );
                send( sockfd , buf , MAXSIZE , 0 );
                while(1){
                    if( FLAG[1] == 0 ){
                        printf("[ 系统提示 ]注册失败！\n");
                        h = 1;
                        break;
                    }else if( FLAG[1] == 1 ){
                        flag = 0;
                        break;
                    }
                }                
            }
            
        }

        printf("[ 系统提示 ]注册成功！你可以登录聊天啦～～ \n");
        printf("×××××××××××××××××××××××××××××××××××××\n\n");
    }
}   

void Select_form()
{//选项界面
    int flag;
    char c,cmd,buf[MAXSIZE];
    Cur_state = 0;
    while(1){
        flag = 1;
        printf("\n×××××××××××××××选项界面×××××××××××××××\n");
        printf("\t1. 好友界面\n");
        printf("\t2. 群列表\n");
        printf("\t3. 未读信息 （%d 条）\n",unread_cnt);
        printf("\t4. 注销\n");
        printf("×××××××××××××××××××××××××××××××××××××\n\n"); 
        while( flag ){
            printf("请输入操作代号：");
            scanf("%c",&cmd);
            if( cmd < '1' || cmd > '4' ){
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");
                while( ( c = getchar() ) != '\n' && c != EOF );
            }
            else 
                break;
        }
        printf("×××××××××××××××××××××××××××××××××××××\n\n");
        while( ( c = getchar() ) != '\n' && c != EOF );
        switch( cmd ){
            case '1':{
                Usr_form();
                break;
            }
            case '2':{
                Group_form();
                break;
            }
            case '3':{
                UnreadMsg_form();
                break;
            }
            case '4':{
                FLAG[9] = -1;
                Comb_msg( buf, "9" , "$" , "0" );
                send( sockfd , buf , MAXSIZE , 0 );
                    printf("[ 系统提示 ]注销成功!感谢您的登录,有缘再见(*^_^*)/bye~！\n");
                    chdir("./..");
                    chdir("./..");
                    Delete_list( Head );
                return;
               break; 
            }

        }
    }
}

void Usr_form()
{//好友界面
    Cur_state = 0;
    Cur_class = USR_CLASS;
    int  flag;
    char cmd ,c;
    while(1){
        flag = 1;
        printf("\n×××××××××××××××好友界面×××××××××××××××\n");
        printf("\t1. 打印好友列表\n");
        printf("\t2. 查看聊天记录\n");
        printf("\t3. 添加好友\n");
        printf("\t4. 删除好友\n");
        printf("\t5. 开始聊天\n");
        printf("\t6. 查看好友申请处理情况 ( %d 条 )\n", apply_result);
        printf("\t7. 处理好友申请 ( %d 条 )\n",apply_num);
        printf("\t8. 返回\n");
        printf("×××××××××××××××××××××××××××××××××××××\n\n");  
        while( flag ){
            printf("请输入操作代号：");
            scanf("%c",&cmd);
            if( cmd < '1' || cmd > '8' ){
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");
                while( ( c = getchar() ) != '\n' && c != EOF );
            }
            else 
                break;
        }
        printf("×××××××××××××××××××××××××××××××××××××\n\n");
        while( ( c = getchar() ) != '\n' && c != EOF );
        switch( cmd ){
            case '1':{
                Print_msgDir(USR_CLASS);
                break;
            }
            case '2':{
                FriendMsg_form();
                break;
            }
            case '3':{
                AddFriend_form();
                break;
            }
            case '4':{
                DelFriend_form();
                break;
            }
            case '5':{
                Select_ChatFriend_form();
                break;
            }
            case '6':{
                watch_friendApply();
                break;
            }
            case '7':{
                handle_friendApply();
                break;
            }
            case '8':{
                return;
                break;
            }

        }   
    }
}

void Group_form()
{//群聊界面
    Cur_state = 0;
    Cur_class = GRP_CLASS;
    int flag;
    char cmd , c;
    Cur_class = GRP_CLASS;
    while(1){
        flag = 1;
        printf("\n×××××××××××××××群聊界面×××××××××××××××\n");
        printf("\t1. 打印群聊列表\n");
        printf("\t2. 查看聊天记录\n");
        printf("\t3. 加入群聊\n");
        printf("\t4. 新建群聊\n");
        printf("\t5. 退出群聊\n");
        printf("\t6. 开始聊天\n");
        printf("\t7. 返回\n");
        printf("×××××××××××××××××××××××××××××××××××××\n\n");  
        while( flag ){
            printf("请输入操作代号：");
            scanf("%c",&cmd);
            if( cmd < '1' || cmd > '7' ){
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");
                while( ( c = getchar() ) != '\n' && c != EOF );
            }
            else 
                break;
        }
        printf("×××××××××××××××××××××××××××××××××××××\n\n");
        while( ( c = getchar() ) != '\n' && c != EOF );
        switch( cmd ){
            case '1':{
                Print_msgDir(GRP_CLASS);
                break;
            }
            case '2':{
                FriendMsg_form();
                break;
            }
            case '3':{
                AddFriend_form();
                break;
            }
            case '4':{
                CreateGrp_form();
                break;
            }
            case '5':{
                DelFriend_form();
                break;
            }
            case '6':{
                Select_ChatFriend_form();
                break;
            }
            case '7':{
                return;
                break;
            }
        }    
    }
}

void FriendMsg_form()
{//查看消息记录
    Cur_state = 0;
    int i ,flag;
    char name[MAX_NAME_SIZE + 2] , c,cmd;
    while(1){
        flag = 1;
        printf("\n×××××××××××××查看消息记录××××××××××××\n\n");
        Print_msgDir( Cur_class );
        while(flag){
            printf("请输入待查聊天名（$0退出）：");
            fgets(  name , MAX_NAME_SIZE + 2 , stdin );

            //判定输入是否正确
            for( i = 0 ; i < MAX_NAME_SIZE + 2 ; i++ ){
                if( name[i] <48 || ( name[i] > 57 && name[i] < 65 ) || ( name[i] > 90 && name[i] < 97 ) || name[i] > 122  )
                    break;
            }

            if( i == MAX_NAME_SIZE + 1){
                printf("[wrong] >> 字符串超长，请保持在%d个字符以内!\n",MAX_NAME_SIZE);
                while( ( c = getchar() ) != '\n' && c != EOF );
            }else if( !strcmp( name , "$0\n" ) ){
                return;
                break;
            }else if( name[i] != '\n' )
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");
            else{
                 name[i] = '\0';               
                if( Is_Friend( name , Cur_class ) )
                    flag = 0;
                else
                    printf("您的好友列表中查无此人，请添加后再查找。\n");
            }
        }
        Read_msgRecord( name  , Cur_class );
        printf("×××××××××××××××××××××××××××××××××××××\n");
        printf("\t1. 与TA聊天～\n");
        printf("\t2. 返回\n");   
        printf("×××××××××××××××××××××××××××××××××××××\n");        
        flag = 1;
        while( flag ){
            printf("请输入操作代号：");
            scanf("%c",&cmd);
            if( cmd < '1' || cmd > '2' ){
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");
                while( ( c = getchar() ) != '\n' && c != EOF );
            }
            else 
                break;
        }
        printf("×××××××××××××××××××××××××××××××××××××\n\n");
        while( ( c = getchar() ) != '\n' && c != EOF );
        switch( cmd ){
            case '1':{
                /*与TA聊天*/
                Chat_form(name);
                break;
            }
            case '2':{
                return;
                break;
            }
        }    
    }   
}

void CreateGrp_form()
{//创建一个群聊
    Cur_state = 0;
    int i ,flag = 1;
    char name[MAX_NAME_SIZE + 2] , c  , buf[MAXSIZE];
    printf("\n×××××××××××××××添加聊天×××××××××××××××\n");

        printf("请输入聊天名称：");
        fgets(  name , MAX_NAME_SIZE + 2 , stdin );

        //判定输入是否正确
        for( i = 0 ; i < MAX_NAME_SIZE + 2 ; i++ ){
            if( name[i] <48 || ( name[i] > 57 && name[i] < 65 ) || ( name[i] > 90 && name[i] < 97 ) || name[i] > 122  )
                break;
        }
        if( i == MAX_NAME_SIZE + 1){
            printf("[wrong] >> 字符串超长，请保持在%d个字符以内!\n",MAX_NAME_SIZE);
            while( ( c = getchar() ) != '\n' && c != EOF );
        }else if( name[i] != '\n' )
            printf("[wrong] >> 您的输入有异常，请重新输入！\n");
        else{ 
            name[i] = '\0';
            if( Is_Friend( name , GRP_CLASS ) ){
                printf("[ 系统提示 ]你已经在群里了，还要建啥群（为你的智商擦一把汗～）\n");
            }else{
                Comb_msg( buf , "4" , name , "0" );
                send( sockfd , buf , MAXSIZE , 0 );
                FLAG[4]=-1;
                while(1){
                    if(FLAG[4] == 0){
                        printf("[ 系统提示 ]很遗憾，这个群已经被人抢占了，不过你可以加入聊天\n");
                        break;
                    }else if(FLAG[4] == 1){
                        Add_friend( name , GRP_CLASS ); 
                        printf("[ 系统提示 ]建群成功，你可以邀请小伙伴们一起来聊天啦～\n");
                        break;
                    }
                }
            }
        } 
    printf("×××××××××××××××××××××××××××××××××××××\n\n"); 
}

void AddFriend_form()
{//添加聊天
    Cur_state = 0;
    int i ,flag = 1;
    char name[MAX_NAME_SIZE + 2] , c , buf[MAXSIZE];
    printf("\n×××××××××××××××添加聊天×××××××××××××××\n");

        printf("请输入聊天名称：");
        fgets(  name , MAX_NAME_SIZE + 2 , stdin );

        //判定输入是否正确
        for( i = 0 ; i < MAX_NAME_SIZE + 2 ; i++ ){
            if( name[i] <48 || ( name[i] > 57 && name[i] < 65 ) || ( name[i] > 90 && name[i] < 97 ) || name[i] > 122  )
                break;
        }
        if( i == MAX_NAME_SIZE + 1){
            printf("[wrong] >> 字符串超长，请保持在%d个字符以内!\n",MAX_NAME_SIZE);
            while( ( c = getchar() ) != '\n' && c != EOF );
        }else if( name[i] != '\n' )
            printf("[wrong] >> 您的输入有异常，请重新输入！\n");
        else{ 
            name[i] = '\0';
            if( !Is_Friend( name , Cur_class ) ){
                if( Cur_class == USR_CLASS ){
                    Comb_msg( buf , "2" , name , "0" );
                    i = 2;
                }else{
                    Comb_msg( buf , "5" , name , "0" );
                    i = 5;
                }
                FLAG[i] = -1;
                send( sockfd , buf , MAXSIZE , 0 );
                
                if( Cur_class == GRP_CLASS ){
                    while(FLAG[i]+1);
                }
            }else{
                printf("[ 系统提示 ]Ta已经是你的好友啦～不必重复添加.嘛，乖乖和好基友愉快的玩耍吧～\n");
            }
            sleep(1);
        }
    
    printf("×××××××××××××××××××××××××××××××××××××\n\n");   
}

void DelFriend_form()
{//退出聊天
    Cur_state = 0;
    int i ,flag = 1;
    char name[MAX_NAME_SIZE + 2] , c ,buf[MAXSIZE];
    printf("\n×××××××××××××××删除聊天×××××××××××××××\n");

        printf("请输入聊天名称：");
        fgets(  name , MAX_NAME_SIZE + 2 , stdin );

        //判定输入是否正确
        for( i = 0 ; i < MAX_NAME_SIZE + 2 ; i++ ){
            if( name[i] <48 || ( name[i] > 57 && name[i] < 65 ) || ( name[i] > 90 && name[i] < 97 ) || name[i] > 122  )
                break;
        }

        if( i == MAX_NAME_SIZE + 1){
            printf("[wrong] >> 字符串超长，请保持在%d个字符以内!\n",MAX_NAME_SIZE);
            while( ( c = getchar() ) != '\n' && c != EOF );
        }else if( name[i] != '\n' )
            printf("[wrong] >> 您的输入有异常，请重新输入！\n");
        else{ 
            name[i] = '\0';            
            if(  !Is_Friend( name , Cur_class ) ){
                printf("[ 系统提示 ]你的好友列表中并没有这样一条记录，你……梦游呢？\n");
                return;
            }
            if( Cur_class == USR_CLASS ){
                Comb_msg( buf , "3" , name , "0" );
                i = 3;
            }else{
                Comb_msg( buf , "6" , name , "0" );
                i = 6;
            }
            FLAG[i] = -1;
            send( sockfd , buf , MAXSIZE , 0 );
                while(FLAG[i]+1);
    }
    sleep(1);
    printf("×××××××××××××××××××××××××××××××××××××\n\n");   
}

void Chat_form( char * name )
{//聊天窗口
    int i , flag;
    char c , buf[MAX_MESSAGE_BUF] ,msg[MAXSIZE];
    printf("\n×××××××××××××××开始聊天×××××××××××××××\n");
    printf("\t输入$exit退出\n");
    printf("×××××××××××××××××××××××××××××××××××××\n\n");    
    Cur_state = 1;
    strcpy( Cur_name , name );
    while(flag){
        chat_usr = 0;
        flag = 1;
//        printf("[%s :]",My_Name);
        fgets(  buf , MAX_MESSAGE_BUF + 2 , stdin );

        for( i = 0 ; i < strlen(buf) ; i++ ){
            if( buf[i] =='\n' || buf[i] =='\0' )
                break;
        }

        if( i == MAX_MESSAGE_BUF + 1){
            printf("[wrong] >> 字符串超长，请保持在%d个字符以内!\n",MAX_MESSAGE_BUF);
            while( ( c = getchar() ) != '\n' && c != EOF );
        }
        else if( !strcmp( buf , "$exit\n" ) ){
            flag = 0;        
            Cur_state = 0;
        }
        else if( buf[i] != '\n' )
            printf("[wrong] >> 您的输入有异常，请重新输入！\n");
        else{ 
            buf[i] = '\0';
            if( Cur_class == USR_CLASS ){
                Comb_msg( msg , "7" , name , buf );
                i = 7;
                if(chat_usr)
                    break;
            }else{
                Comb_msg( msg , "8" , name , buf );
                i = 8;
            }
            FLAG[i] = -1;
            send( sockfd , msg , MAXSIZE , 0 );
            printf("[%s :]%s\n",My_Name,buf);
        }
    }
    
    
}

void Select_ChatFriend_form()
{//开始聊天
    Cur_state = 0;
    int i ,flag = 1;
    char name[MAX_NAME_SIZE + 2] , c;
    printf("\n×××××××××××××××聊天窗口×××××××××××××××\n");
    while(flag){
        printf("请输入聊天名称：");
        fgets(  name , MAX_NAME_SIZE + 2 , stdin );

        //判定输入是否正确
        for( i = 0 ; i < MAX_NAME_SIZE + 2 ; i++ ){
            if( name[i] <48 || ( name[i] > 57 && name[i] < 65 ) || ( name[i] > 90 && name[i] < 97 ) || name[i] > 122  )
                break;
        }

        if( i == MAX_NAME_SIZE + 1){
            printf("[wrong] >> 字符串超长，请保持在%d个字符以内!\n",MAX_NAME_SIZE);
            while( ( c = getchar() ) != '\n' && c != EOF );
        }else if( name[i] != '\n' )
            printf("[wrong] >> 您的输入有异常，请重新输入！\n");
        else{ 
            flag = 0;
            name[i] = '\0';
        }
    }
    printf("×××××××××××××××××××××××××××××××××××××\n\n");
    /*判断，与好友聊天  Cur_state = 1;*/
    if(Is_Friend( name , Cur_class ))
        Chat_form(name);
    else
        printf("[ 系统提示 ]你好像并没有这个好友，本系统表示为你的智商堪忧（白眼）……\n");
}

void UnreadMsg_form()
{//未读信息
    Cur_state = 0;
   int flag = 1 ,i;
    char cmd , name[MAX_NAME_SIZE + 2] , c;
    while(1){
        printf("\n×××××××××××××××未读信息×××××××××××××××\n\n");
        Print_unread( Head );
        printf("×××××××××××××××××××××××××××××××××××××\n");  
        printf("\t1. 未读信息操作（私聊）\n");
        printf("\t2. 未读信息操作（群聊）\n");
        printf("\t3. 退出\n");    
        printf("×××××××××××××××××××××××××××××××××××××\n");  
        while( flag ){
            printf("请输入操作代号：");
            scanf("%c",&cmd);
            if( cmd < '1' || cmd > '3' ){
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");
                while( ( c = getchar() ) != '\n' && c != EOF );
            }
            else 
                break;
        }
        while( ( c = getchar() ) != '\n' && c != EOF );
        switch( cmd ){
            case '1':{
//                Print_msgDir(USR_CLASS);
                Cur_class = USR_CLASS;
                break;
            }
            case '2':{
//                Print_msgDir(GRP_CLASS);
                Cur_class = GRP_CLASS;
                break;
            }
            case '3':{
                return;
                break;
            }
        }  
        printf("×××××××××××××××查看消息记录×××××××××××××××\n");
        while(flag){
            printf("请输入待查聊天名：($0返回)");
            fgets(  name , MAX_NAME_SIZE + 2 , stdin );

            //判定输入是否正确
            for( i = 0 ; i < MAX_NAME_SIZE + 2 ; i++ ){
                if( name[i] <48 || ( name[i] > 57 && name[i] < 65 ) || ( name[i] > 90 && name[i] < 97 ) || name[i] > 122  )
                    break;
            }

            if( i == MAX_NAME_SIZE + 1){
                printf("[wrong] >> 字符串超长，请保持在%d个字符以内!\n",MAX_NAME_SIZE);
                while( ( c = getchar() ) != '\n' && c != EOF );
            }else if( !strcmp( name , "$0\n" ) ){
                return;
                break;
            }else if( name[i] != '\n' )
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");
            else{
                name[i] = '\0'; 
                if( !Check_unread(Head , name ,Cur_class) ){
                    Read_msgRecord( name  , Cur_class );
                    flag = 0;
                }

            }
        }
        printf("×××××××××××××××××××××××××××××××××××××\n");
        printf("\t1. 与TA聊天～\n");
        printf("\t2. 返回\n");   
        
        //打印name对应的好友消息列表
        flag = 1;
        while( flag ){
            printf("请输入操作代号：");
            scanf("%c",&cmd);
            if( cmd < '1' || cmd > '2' ){
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");
                while( ( c = getchar() ) != '\n' && c != EOF );
            }
            else 
                break;
        }
        while( ( c = getchar() ) != '\n' && c != EOF );
        switch( cmd ){
            case '1':{
                Chat_form(name);
                break;
            }
            case '2':{
                return;
                break;
            }
        }        
    }
}
