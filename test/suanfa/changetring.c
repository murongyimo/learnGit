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

int ChangeAtoB( char * A ,char * B ,int len_A ,int len_B )
{
    //比较两个字符串并输出
    int i,j,min,add,del,chg;
    char min_A[MAXSTR],min_B[MAXSTR];
    A[len_A] = '\0';
    B[len_B] = '\0';//改变字符串长度
    i = strlen(A);
    j = strlen(B);
    /*当有一个字符串为空时，最短长度即为插入（或者删除）非空字符串的长度
    * 当有两个字符串为空时，最短长度即为0*/
    if( i == 0 && j == 0 )
        return 0;
    else if( i == 0 && j > 0 )
        return j;
    else if( i > 0 && j == 0 )
        return i;
    else if( i>0 && j>0 && A[i-1] == B[j-1] )
    /*当最后一个字符相同的时候，两个字符串的最后一个字符都不需处理，递归处理字符串-1即可*/
        return ChangeAtoB(A,B,i-1,j-1);
    else if( i>0 && j>0 && A[i-1] != B[j-1] ){
    /*通过递归寻找子问题最优解，字符串A可能发生的改变有三种：增（add），删（del），改（chg）
      将A与B的值暂存在min_A与min_B中，继续寻找子问题的最优解
        i，j分别为字符串A与B的长度
        add：字符串A末尾增加一个字符，下一次比较i不变，j-1
        del：字符串A末尾删除一个字符，下一次比较i-1, j不变
        chg：字符串A末尾字符改为字符串B末尾字符，下一次比较i-1,j-1
    */
        add = ChangeAtoB(strcpy(min_A,A),strcpy(min_B,B),i,j-1);
        del = ChangeAtoB(strcpy(min_A,A),strcpy(min_B,B),i-1,j);
        chg = ChangeAtoB(strcpy(min_A,A),strcpy(min_B,B),i-1,j-1);
        return MIN(add,del,chg) + 1;
        //返回三种情况中最小的一种需要比较的次数加一
    }else{
        printf("!!!string change error!!!\n");
        exit(-2);
    }
}

int main(void)
{
    char A[MAXSTR],B[MAXSTR],s[10];
    int min;
    while(1){
        printf(">>*****编辑距离问题*****<<\n");
        Input_AB(A,B);
        //输入A和B两个字符串
        min = ChangeAtoB(A,B,strlen(A),strlen(B));
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
