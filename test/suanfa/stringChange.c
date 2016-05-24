/*************************************************************************
	> File Name: stringChange.c
	> Author: 
	> Mail: 
	> Created Time: 2016年04月30日 星期六 14时34分17秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXSTR 100

int MIN( int i,int j,int k )
{
    //比较三个数字中的最小值，将最小值返回。
    int min = i;
    if( j < min )
        min = j;
    if( k < min )
        min = k;
    return min;
}

void Input_AB(char * A , char * B)
{
    //输入待比较的字符串A与B
    if( A && B ){ 
        printf(">>请输入字符串中A的内容<<：\n");
        scanf("%s",A);
        printf(">>请输入字符串中B的内容：<<\n");
        scanf("%s",B);
    }else{
        printf("!!!there is something wrong with A or B!!!\n");
        exit(-1);
    }
}

int ChangeAtoB( char * A ,char * B )
{
    //比较两个字符串并输出
    int i,j,a_length,b_length,d[MAXSTR][MAXSTR];
    a_length = strlen(A);
    b_length = strlen(B);
    
    for( i = 0 ; i < a_length ; i++ )
    {
        for( j = 0 ; j < b_length ; j++ )
        {
            if( A[i] != B[j] && i != 0 && j != 0)
                d[i][j] = MIN(d[i-1][j] , d[i][j-1] , d[i-1][j-1]) + 1;
            else if( i == 0 && j == 0 )     //设置初始情况，A[0]=B[0]，则d[0][0] = 0,否则d[0][0] = 1
            {
                if( A[i] == B[j] )
                    d[i][j] = 0;
                else
                    d[i][j] = 1;
            }
            else if( i == 0 )   //若i = 0 && j ！= 0则只可进行增加操作
            {
                if( A[i] == B[j] )
                    d[i][j] = d[i][j-1];
                else
                    d[i][j] = d[i][j-1] + 1;
            }
            else if( j == 0 )   //若i ！= 0 && j = 0则只可进行删除操作
            {
                if( A[i] == B[j] )
                    d[i][j] = d[i-1][j];
                else
                    d[i][j] = d[i-1][j] + 1;
            }
            else                //若非以上几种情况，则A[i] = B[j],不做更改。 
                d[i][j] = d[i-1][j-1];    
        }
    }
    return d[a_length1][b_length-1];
}

int main(void)
{
    char A[MAXSTR],B[MAXSTR],s[10];
    int min;
    while(1){
        printf(">>*****编辑距离问题*****<<\n");
        Input_AB(A,B);
        //输入A和B两个字符串
        min = ChangeAtoB(A,B);
        //计算两个字符串间最短转换距离
        printf("==>>字符串%s -> %s 最短距离为：%d\n",A,B,min);
        printf(">>*****问题结束*****<<\n");
        //点击Y或者y键继续查找，否则跳出循环结束
        getchar();
        printf(">>[Y]键继续——<<\n");
        scanf("%s",s);
        if( !strncmp(s,"Y",1) || !strncmp(s,"y",1));
        else
            break;
    }
    printf(">>*****程序结束*****<<\n");
        return 0;
}
