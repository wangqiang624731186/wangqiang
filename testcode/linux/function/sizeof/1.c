/*************************************************************************
	> File Name: 1.c
	> Author: wangqiang
	> Mail: wangqiang.neu@neusoft.com 
	> Created Time: Thu 04 Sep 2014 04:04:34 PM CST
 ************************************************************************/

#include<stdlib.h>
#include<stdio.h>

void test(char t[100])
{
	char *p = t;
	printf("sizeof(p)=%d\n",sizeof(p));
	printf("sizeof(t)=%d\n",sizeof(t));
	char m[100];
	printf("sizeof(m)=%d\n",sizeof(m));
}
int main()
{
	char *p;
	printf("sizeof(p)=%d\n",sizeof(p));
	test(0);
	return 0;
}
