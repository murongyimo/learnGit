/*************************************************************************
	> File Name: my_chmod.c
	> Author: 
	> Mail: 
	> Created Time: 2016年04月23日 星期六 10时20分24秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc,char * argv[])
{
    int     mode;
    int     mode_u;
    int     mode_g;
    int     mode_o;
    char    * path;

    /*检查参数个数的合法性*/
    if(argc<3)
    {
        printf("%s <mode num> <target file>\n",argv[0]);
        exit(0);
    }
    /*获取命令行参数*/
    mode = atoi(argv[1]);
    if(mode>777 || mode<0)
    {
        printf("mode num error.\n");
        exit(0);
    }
    mode_u = mode/100;
    mode_g = (mode - mode_u * 100)/10;
    mode_o = mode%10;
    mode = mode_o + mode_g * 8 + mode_u * 8 * 8;
    path = argv[2];

    if(chmod(path,mode) == -1)
    {
        perror("chmod error!");
        exit(1);
    }
    return 0;
}
