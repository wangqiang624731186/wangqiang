/*************************************************************************
	> File Name: vardefine.c
	> Author: wangqiang
	> Mail: 624731186@qq.com 
	> Created Time: 2016年02月16日 星期二 11时37分57秒
 ************************************************************************/

#include<stdlib.h>
#include<stdio.h>

int main(int argc,char** argv)
{
    int a[argc];

    a[0] = 0;
    a[1] = 1;

    printf("%ld\n",sizeof(a));

    return 0;
}
