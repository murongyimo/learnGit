/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2016年05月15日 星期日 18时50分01秒
 ************************************************************************/


void Start_form()
{//初始界面
    int i ,flag , h;
    char passwd[MAX_PASSWD_SIZE + 2] ,name[MAX_NAME_SIZE + 2] , c;
    Cur_state = 0;
    while(1){
        flag = 1;
        h = 0;
        printf("\n×××××××××××××××登陆界面×××××××××××××××\n");
        printf("     _$0_（退出）     _$1_(注册)\n");
        printf("×××××××××××××××××××××××××××××××××××××\n\n");
        while(flag){
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
            else if( !strcmp( name , "$0\n" ) )
                exit(0);
            else if( !strcmp( name , "$1\n" ) ){
                register_form();         
                h = 1;
                flag = 0;
            }
            else if( name[i] != '\n' )
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");
        
            else{ 
                /*将name传到服务器上验证*/
                name[i] = '\0';
                FLAG[0] = -1;
                Comb_msg( buffer, "1" , name , "0" );
                send( sockfd , buffer , MAXSIZE , 0 );
                while(1){
                    if(FLAG[0] == 1){//当服务器检测到用户名存在时
                        flag = 0;
                        break;
                    }else if( FLAG[0] == 0){
                        h = 1;
                        printf("该用户名不存在！请重新输入！\n");
                        break;
                    }
                }
                
            }
        }
        if( h == 1 ) 
            continue;
        flag = 1;
        while(flag){

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
            else if( !strcmp( name , "$0\n" ) )
                exit(0);
            else if( !strcmp( name , "$1\n" ) )
                register_form();                
            else if( passwd[i] != '\n' )
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");

            else{
                /*将passwd传到服务器上验证*/
                passwd[i] = '\0';    
                FLAG[0] = -1;
                Comb_msg( buffer, "1" , passwd , "1" );
                send( sockfd , buffer , MAXSIZE , 0 );
                while(1){
                    if(FLAG[0] == 0){
                        printf("密码错误！请重新输入！\n");
                        h = 1;
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
        printf("登录成功！ \n");
        printf("×××××××××××××××××××××××××××××××××××××\n\n");
        strcpy(My_Name,name);
        Select_form();
    }
}

void register_form()
{//注册界面
    
    int i ,flag = 1 ,h;
    char passwd[MAX_PASSWD_SIZE + 2] ,name[MAX_NAME_SIZE + 2] , c;
    Cur_state = 0;
    while(1){
        h = 0;
        My_ID = 0;
        printf("\n×××××××××××××××注册界面×××××××××××××××\n");
        printf("     _$0_（退出）     _$1_(登录)\n");
        printf("×××××××××××××××××××××××××××××××××××××\n\n");
        while(flag){
            flag = 1;
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
            else if( !strcmp( name , "$0\n" ) )
                exit(0);
            else if( !strcmp( name , "$1\n" ) )
                return;         
            else if( name[i] != '\n' )
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");
        
            else{ 
                /*将name传到服务器上验证*/
                name[i] = '\0';
                FLAG[1] = -1;
                Comb_msg( buffer, "1" , name , "0" );
                send( sockfd , buffer , MAXSIZE , 0 );
                while(1){
                    if(FLAG[1] == 0){//当服务器检测到用户名不存在时
                        flag = 0;
                        break;
                    }else if( FLAG[1] == 1 ){
                        printf("该用户名已被注册，请选择其他用户名！\n");
                        h = 1;
                        break;
                    }
                }
                
            }
        }
        if(h == 1)
            continue;
        flag = 1;
        while(flag){

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
            else if( !strcmp( name , "$0\n" ) )
                exit(0);
            else if( !strcmp( name , "$1\n" ) )
                return;       
            else if( passwd[i] != '\n' )
                printf("[wrong] >> 您的输入有异常，请重新输入！\n");

            else{
                /*将passwd传到服务器上验证*/
                passwd[i] = '\0';      
                FLAG[1] = -1;
                Comb_msg( buffer, "1" , passwd , "1" );
                send( sockfd , buffer , MAXSIZE , 0 );
                while(1){
                    if(FLAG[1] == 0){
                        printf("注册失败！\n");
                        h = 1;
                        break;
                    }else if( FLAG[1] == 1 ){
                        flag = 0;
                        break;
                    }
                }                
                

            }
        }
        if(h == 1)
            continue;
        printf("注册成功！你可以登录聊天啦～～ \n");
        printf("×××××××××××××××××××××××××××××××××××××\n\n");
        return;
    }
}    

void Select_form()
{//选项界面
    int flag;
    char c,cmd;
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
                Comb_msg( buffer, "9" , "0" , "0" );
                send( sockfd , buffer , MAXSIZE , 0 );
                while(1){
                    if(FLAG[9] == 0){
                        printf("注销失败，请重试！\n");
                        break;
                    }else if( FLAG[1] == 1 ){
                        printf("注销成功!感谢您的登录,有缘再见(*^_^*)/bye~！\n");
                        return;
                    }
                }                
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
        printf("\t6. 返回\n");
        printf("×××××××××××××××××××××××××××××××××××××\n\n");  

        while( flag ){
            printf("请输入操作代号：");
            scanf("%d",&cmd);
            if( cmd < '1' || cmd > '6' ){
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
        printf("\t4. 退出群聊\n");
        printf("\t5. 开始聊天\n");
        printf("\t6. 返回\n");
        printf("×××××××××××××××××××××××××××××××××××××\n\n");  
        while( flag ){
            printf("请输入操作代号：");
            scanf("%d",&cmd);
            if( cmd < '1' || cmd > '6' ){
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
                DelFriend_form();
                break;
            }
            case '5':{
                Select_ChatFriend_form();
                break;
            }
            case '6':{
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
        printf("\n×××××××××××××查看消息记录××××××××××××\n");
        while(flag){
            printf("请输入待查聊天名：");
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
            scanf("%d",&cmd);
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

void AddFriend_form()
{//添加聊天
    Cur_state = 0;
    int i ,flag = 1;
    char name[MAX_NAME_SIZE + 2] , c;
    printf("\n×××××××××××××××添加聊天×××××××××××××××\n");
//    while(flag){
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
                    Comb_msg( buffer , "2" , name , "0" );
                    i = 2;
                }else{
                    Comb_msg( buffer , "5" , name , "0" );
                    i = 5;
                }
                FLAG[i] = -1;
                send( sockfd , buffer , MAXSIZE , 0 );
                while(1){
                    if( FLAG[i] == 1 ){
                        Add_friend(name , Cur_class);  
                        break;
                    }else if(FLAG[i]==0){
                        printf("[ 系统提示 ]对方拒绝了你的好友申请～魅力值不够呀，亲～\n");
                        break;
                    }
                }
//                flag = 0;

            /*在Add_friend()中加入与服务器的交互*/
            }else{
                printf("[ 系统提示 ]Ta已经是你的好友啦～不必重复添加.嘛，乖乖和好基友愉快的玩耍吧～\n");
            }
        }
//    }
    printf("×××××××××××××××××××××××××××××××××××××\n\n");   
}

void DelFriend_form()
{//退出聊天
    Cur_state = 0;
    int i ,flag = 1;
    char name[MAX_NAME_SIZE + 2] , c;
    printf("\n×××××××××××××××删除聊天×××××××××××××××\n");
//    while(flag){
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
//            flag = 0;
            name[i] = '\0';
            if(Is_Friend( name , Cur_class )){
                if( Cur_class == USR_CLASS ){
                    Comb_msg( buffer , "3" , name , "0" );
                    i = 3;
                }else{
                    Comb_msg( buffer , "6" , name , "0" );
                    i = 6;
                }
                FLAG[i] = -1;
                send( sockfd , buffer , MAXSIZE , 0 );
                while(1){
                    if( FLAG[i] == 1 ){
                        Del_friend( name , Cur_class ); 
                        printf("[ 系统提示 ]%s表示：%s你好狠的心～就酱紫删掉伦家QAQ～～\n",name,My_Name);
                        break;
                    }else if(FLAG[i]==0){
                        printf("[ 系统提示 ]删除失败，看来你们缘分未尽，绝对不是服务器的错，喵～（无辜脸）\n");
                        break;
                    }
                }            

            /*在Del_friend()中加入与服务器的交互*/
        }
    }
    printf("×××××××××××××××××××××××××××××××××××××\n\n");   
}

void Chat_form( char * name )
{//聊天窗口
    int i , flag;
    char c;
    printf("\n×××××××××××××××开始聊天×××××××××××××××\n");
    printf("\t输入$exit退出\n");
    printf("×××××××××××××××××××××××××××××××××××××\n\n");    
    Cur_state = 1;
    strcpy( Cur_name , name );
    while(flag){
        flag = 1;
        printf("[%s:]",My_Name);
        fgets(  buffer , MAX_MESSAGE_BUF + 2 , stdin );

        for( i = 0 ; i < MAX_MESSAGE_BUF + 2 ; i++ ){
            if( buffer[i] =='\n' || buffer[i] =='\0' )
                break;
        }

        if( i == MAX_MESSAGE_BUF + 1){
            printf("[wrong] >> 字符串超长，请保持在%d个字符以内!\n",MAX_MESSAGE_BUF);
            while( ( c = getchar() ) != '\n' && c != EOF );
        }
        else if( !strcmp( buffer , "$exit\n" ) ){
            flag = 0;        
            Cur_state = 0;
        }
        else if( buffer[i] != '\n' )
            printf("[wrong] >> 您的输入有异常，请重新输入！\n");
        else{ 
            buffer[i] = '\0';
            if( Cur_class == USR_CLASS ){
                Comb_msg( buffer , "7" , name , msg_buf );
                i = 7;
            }else{
                Comb_msg( buffer , "8" , name , msg_buf );
                i = 8;
            }
            FLAG[i] = -1;
            send( sockfd , buffer , MAXSIZE , 0 );
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
        printf("\n×××××××××××××××未读信息×××××××××××××××\n");
        Clear_unread( Head );
        Head = Read_unread();
        Print_unread( Head );
        printf("×××××××××××××××××××××××××××××××××××××\n");  
        printf("\t1. 私聊\n");
        printf("\t2. 群聊\n");
        printf("\t3. 退出\n");    
        printf("×××××××××××××××××××××××××××××××××××××\n");  
        while( flag ){
            printf("请输入操作代号：");
            scanf("%d",&cmd);
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
                Print_msgDir(USR_CLASS);
                Cur_class = USR_CLASS;
                break;
            }
            case '2':{
                Print_msgDir(GRP_CLASS);
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
            printf("请输入待查聊天名：");
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
                if( !Check_unread(Head , name ,Cur_class) ){
                    Write_unread( Head );
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
            scanf("%d",&cmd);
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
