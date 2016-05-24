/*************************************************************************
	> File Name: checkerrno.c
	> Author: 
	> Mail: 
	> Created Time: 2016年04月26日 星期二 19时33分51秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main()
{
    FILE    *stream;
    char    *filename="test";
    errno=0;
    stream = fopen(filename,"r");
    if(stream == NULL)
    {
        printf("open file %s failed,errno is %d\n",filename,errno);
    }else{
        printf("open file %s successfully.\n",filename);
    }
    return 0;
}
