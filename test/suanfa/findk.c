/*************************************************************************
	> File Name: FindMaxK.c
	> Author: 
	> Mail: 
	> Created Time: 2016年04月30日 星期六 17时56分37秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSTR 50

int getI( char * s , int w )
{//将字符串s从第w-1到最后一个字符转换为十进制数字
    int i = 0;
    char str[MAXSTR];
    while( s[w] )
        str[i++] = s[w++];
    str[i]='\0';
    return atoi(str);
}

int MaxI( char * s , int n , int k  )
{ 
 /* s：待分割字符串
    n：待分割字符串长度
    k：即将分割的段数
    str：存储分割情况*/
    char max_s[MAXSTR] ;
    int w,I,max_I = -1,max_w = k-1;
    s[n] = '\0';
    if( k == 1 )
    //若k=1,即只分割为1段，直接返回
        return atoi(s);
    else{
    //k不为1,则最后一段开始位置满足w>=k-1 && w<n
    //分别求出各个w情况下将剩余的字符串分解为k-1段时的最大k乘积，与最后一段相乘，返回最大情况。
        for( w = k-1 ; w < n ; w++ )
        {
            I = MaxI( strcpy( max_s , s ) , w , k - 1 ) * getI( s , w );
            if( I > max_I ){
                max_I = I ;
                max_w = w ;
            }
        }
        return max_I;
    }
}

int main( void )
{
    char s[MAXSTR];
    int k , max;
    printf(">>*****程序开始*****<<\n");
    while(1){
        //使用字符串数组str存储分段情况
        //分别输入要分割的数字s及分割的段数k
        printf(">>*****最大k乘积问题*****<<\n");
        printf(">>***请输入要分割的数字s***<<\n");
        scanf("%s",s); 
        printf(">>***请输入分割段数k***<<\n");
        scanf("%d",&k);
        //调用MaxI函数进行分段
        max = MaxI(s,strlen(s),k);
        printf("==>>%s最大%d乘积为：%d\n",s,k,max);
        printf("\n>>*****问题结束*****<<\n");
        getchar();
        //判断程序继续或者结束
        printf(">>[Y]键继续<<\n");
        scanf("%s",s);
        if( !strncmp(s,"Y",1) || !strncmp(s,"y",1));
        else
            break;
    }
    printf(">>*****程序结束*****<<\n");
    return 0;
}
