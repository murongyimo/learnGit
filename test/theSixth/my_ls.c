/*************************************************************************
	> File Name: my_ls.c
	> Author: 
	> Mail: 
	> Created Time: 2016年04月23日 星期六 11时17分40秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<linux/limits.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>

#define PARAM_NONE  0   //无参
#define PARAM_A     1   //-a：显示所有文件
#define PARAM_L     2   //-l：一行显示一个文件的详细信息
#define MAXROWLEN   80  //一行显示的最多字符数

int g_leave_len = MAXROWLEN;
int g_maxlen;
/*错误处理函数，打印出错误所在行的行数和错误信息*/
void myerr(const char *err_string,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(err_string);
    exit(1);
}

/*获取文件属性并打印*/
void display_attribute(struct stat buf,char * name)
{
    char             buf_time[32];
    struct passwd   * psd;
    struct group    * grp;
    if(S_ISLNK(buf.st_mode))
        printf("l");
    else if(S_ISREG(buf.st_mode))
        printf("-");
    else if(S_ISDIR(buf.st_mode))
        printf("d");
    else if(S_ISCHR(buf.st_mode))
        printf("c");
    else if(S_ISBLK(buf.st_mode))
        printf("b");
    else if(S_ISFIFO(buf.st_mode))
        printf("f");
    else if(S_ISSOCK(buf.st_mode))
        printf("s");

/*获取打印文件所有者的权限*/
    if(buf.st_mode & S_IRUSR)
        printf("r");
    else
        printf("-");
    if(buf.st_mode & S_IWUSR)
        printf("w");
    else
        printf("-");
    if(buf.st_mode & S_IXUSR)
        printf("x");
    else
        printf("-");
/*获取打印文件所在用户组的权限*/
    if(buf.st_mode & S_IRGRP)
        printf("r");
    else
        printf("-");
    if(buf.st_mode & S_IWGRP)
        printf("w");
    else
        printf("-");
    if(buf.st_mode & S_IXGRP)
        printf("x");
    else
        printf("-");
/*获取打印文件针对其他用户的权限*/
    if(buf.st_mode & S_IROTH)
        printf("r");
    else
        printf("-");
    if(buf.st_mode & S_IWOTH)
        printf("w");
    else
        printf("-");
    if(buf.st_mode & S_IXOTH)
        printf("x");
    else
        printf("-");
/*获得链接数，用户名，组名，文件大小，修改时间，文件名并打印*/
    psd = getpwuid(buf.st_uid);
    grp = getgrgid(buf.st_gid);
    printf("  %-4d%-6s%-6s",buf.st_nlink,psd->pw_name,grp->gr_name);
    printf("%6d",buf.st_size);//文件大小
    strcpy(buf_time,ctime(&buf.st_mtime));
    buf_time[strlen(buf_time)-1]='\0';
    printf("  %s",buf_time);
}

/*当没有使用-l时，打印一个文件名，打印时上下对齐*/
void display_single(char * name)
{
    int i,len;
//若本行不足以打印一个文件名则换行
    if(g_leave_len<g_maxlen)
    {
        printf("\n");
        g_leave_len=MAXROWLEN;
    }
    len = strlen(name);
    len = g_maxlen - len;
    printf("%-s",name);
    for(i=0;i<len;i++)
        printf(" ");
    printf(" ");
    g_leave_len-=(g_maxlen+2);
}
/*
 根据命令参数和完整路径名显示目标文件
 参数flag：命令行参数
 参数pathname：包含了文件的路径名
*/
void display(int flag,char * pathname)
{
    int i,j;
    struct stat buf;
    char name[NAME_MAX+1];
/*从路径中解析出文件名*/
    for(i=0,j=0;i<strlen(pathname);i++)
    {
        if(pathname[i]=='/')
        {
            j=0;
            continue;
        }
        name[j++] = pathname[i];
    }
    name[j]='\0';
/*使用lstat而不是stat以方便解析链接文件*/
    if(lstat(pathname,&buf)==-1)
        myerr("stat",__LINE__);
    switch(flag)
    {
        case PARAM_NONE://没有参数
            if(name[0]!='.')
                display_single(name);
            break;
        case PARAM_A://有-a参数
            display_single(name);
            break;
        case PARAM_L://有-l参数
            if(name[0]!='.')
            {
                display_attribute(buf,name);
                printf("  %-s\n",name);
            }
            break;
        case PARAM_A+PARAM_L://有-a和-l两个参数
            display_attribute(buf,name);
            printf("  %s\n",name);
            break;
        default:
            break;
    }
}

void display_dir(int flag_param,char * path)
{
    DIR             *dir;
    struct dirent   *ptr;
    int             count = 0;
    char            filenames[256][PATH_MAX+1],temp[PATH_MAX+1];
    //获得该目录下文件总数及最长文件名：
    dir = opendir(path);
    if(dir==NULL)
        myerr("opendir",__LINE__);
    while((ptr=readdir(dir))!=NULL)
    {
        if(g_maxlen<strlen(ptr->d_name))
            g_maxlen = strlen(ptr->d_name);
        count++;
    }
    closedir(dir);
    if(count>256)
        myerr("too many files under this dir.",__LINE__);

    int i , j , len = strlen(path);
    //获取该目录下的所有文件名
    dir = opendir(path);
    for(i=0;i<count;i++)
    {
        if((ptr = readdir(dir))==NULL)
            myerr("readdir",__LINE__);
        strncpy(filenames[i],path,len);
        filenames[i][len]='\0';
        strcat(filenames[i],ptr->d_name);
        filenames[i][len+strlen(ptr->d_name)]='\0';
    }
//使用冒泡排序法给文件名排序，排序后文件名按照字母顺序存储于filenames.
    for(i=0;i<count-1;i++)
        for(j=0;j<count-i-1;j++)
        {
            if(strcmp(filenames[j],filenames[j+1])>0)
            {
                strcpy(temp,filenames[j+1]);
                temp[strlen(filenames[j+1])]='\0';
                strcpy(filenames[j+1],filenames[j]);
                filenames[j+1][strlen(filenames[j])]='\0';
                strcpy(filenames[j],temp);
                filenames[j][strlen(temp)]='\0';
            }
        }
    for(i=0;i<count;i++)
        display(flag_param,filenames[i]);
    closedir(dir);
//若命令中没有-l，打印一个换行符
    if((flag_param & PARAM_L)==0)
        printf("\n");
}

int main(int argc,char * argv[])
{
    int     i,j,k,num;
    char    path[PATH_MAX+1];
    char    param[32];
    int     flag_param=PARAM_NONE;
    struct stat buf;
/*命令行参数的分析，分析-a，-l,-al,-la选项*/
    j=0;
    num=0;
    for(i=1;i<argc;i++)
        if(argv[i][0]=='-')
        {
            for(k=1;k<strlen(argv[i]);k++,j++)
                 param[j]=argv[i][k];
             num++;
         }
/*仅支持a和l，如果有其他选项则会报错*/
    for(i=0;i<j;i++)
    {
        if(param[i]=='a'){
            flag_param|=PARAM_A;
            continue;
        }else if(param[i]=='l'){
            flag_param|=PARAM_L;
            continue;
        }else{
            printf("my_ls:invalid option -%c\n",param[i]);
            exit(1);
        }
    }
    param[j]='\0';
//如果没有输入文件名或目录，就显示当前目录
    if((num+1)==argc){
        strcpy(path,"./");
        path[2]='\0';
        display_dir(flag_param,path);
        return 0;
        }
    i=1;
    do{
//若不是目标文件名或者目录，解析下一个命令参数：
        if(argv[i][0]=='-'){
            i++;
            continue;
        }else{
            strcpy(path,argv[i]);
            //若目标文件或者目录不存在，报错并退出程序
            if(stat(path,&buf)==-1)
                myerr("stat",__LINE__);
            if(S_ISDIR(buf.st_mode)){
            //argv[i]是一个目录
            //若目录的最后一个字符不是'/',加上'/'
                if(path[strlen(argv[i])-1]!='/')
                {
                    path[strlen(argv[i])]='/';
                    path[strlen(argv[i])+1]='\0';
                }else
                    path[strlen(argv[i])]='\0';
                display_dir(flag_param,path);
                i++;
            }
            else{
                display(flag_param,path);
                i++;
            }
        }
    }while(i<argc);
    return 0;
}



