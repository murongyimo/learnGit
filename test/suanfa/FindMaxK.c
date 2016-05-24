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

int getI( char * s , int m ,int n )
{//将字符串s从第m到第n个字符转换为十进制数字
    int i = 0;
    char str[MAXSTR];
    m--;
    while( m < n )
        str[i++] = s[m++];
    str[i]='\0';
    return atoi(str);
}

int MaxI( char * s , int k  )
{ 
 /* s：待分割字符串
    k：即将分割的段数
*/
    int wei[MAXSTR][MAXSTR],i,j,w,I;
    //将二维数组初始化，赋值为0
    for( i = 1 ; i <= strlen( s ) ; i++ )
        for( j = 1 ; j <= k ; j++ )
            wei[i][j] = 0;
    //wei[i][j]中，i代表待转换的数字长度，j代表要划分的段数。
    for( i = 1 ; i <= strlen( s ) ; i++ )
    {
        for( j = 1 ; j <= i && j <= k ; j++ )
        {
            if( j == 1 )//当j为1时，即将数字分为1段，最大值即为数字本身
            wei[i][j] = gI( s , 1 , i );
            else
            {
                //j！=1时，wei[i][j]的值为所有（j-1段的最大值）×（第j段）中的最大值
                for( w = j-1 ; w < i ; w++ )
                {
                    I = wei[w][j-1] * getI( s , w+1 , i ) ;
                    if( wei[i][j] < I ) 
                        wei[i][j] = I;
                }
            }
        }
    }
    return wei[i-1][j-1];
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
        max = MaxI(s,k);
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
