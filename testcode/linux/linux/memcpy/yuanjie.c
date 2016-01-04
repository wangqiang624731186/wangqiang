/*************************************************************************
	> File Name: yuanjie.c
	> Author: wangqiang
	> Mail: wangqiang.neu@neusoft.com 
	> Created Time: Wed 05 Nov 2014 10:32:23 AM CST
 ************************************************************************/

#include<stdlib.h>
#include<stdio.h>

int main()
{
	char buf[32];
	char ack = 0;
	printf("11111111111111111111111111111\n");
	memcpy(&ack,buf + 32 * 16 *16 ,1);
	printf("2222222222222222222222222222\n");
}
