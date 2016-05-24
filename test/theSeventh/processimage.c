/*************************************************************************
	> File Name: processimage.c
	> Author: 
	> Mail: 
	> Created Time: 2016年04月22日 星期五 20时42分16秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc,char * argv[],char ** environ)
{
    int i;

    printf(">>I am a process image !\n");
    printf(">>My pid = %d ,my parent's pid = %d \n",getpid(),getppid());
    printf(">>uid = %d,gid = %d\n",getuid(),getgid());

    for(i=1;i<argc;i++)
    printf(">>>argv[%d]:%s\n",i,argv[i]);
}
