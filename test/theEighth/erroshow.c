/*************************************************************************
	> File Name: erroshow.c
	> Author: 
	> Mail: 
	> Created Time: 2016年04月26日 星期二 20时19分53秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

FILE * open_file(char * filename)
{
    FILE * stream;
    errno = 0;
    stream = fopen(filename,"r");
    if(stream==NULL)
    {
        printf("can not open the file %s,the reason is %s\n",filename,strerror(errno));
        exit(-1);
    }
    else
        return stream;
}

int main(void)
{
    char * filename="test";
    open_file(filename);
    return 0;
}
