/*************************************************************************
	> File Name: umask.c
	> Author: wangqiang
	> Mail: wangqiang.neu@neusoft.com 
	> Created Time: Fri 05 Sep 2014 05:13:36 PM
 ************************************************************************/

#include<stdlib.h>
#include<stdio.h>

#include <unistd.h>
#include <sys/stat.h>
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
int main(void)
{
	mode_t mask=umask(0);
	if(creat("foo",RWRWRW)<0)
		printf("create error for foo\n");
	umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
	if(creat("bar",RWRWRW)<0)
		printf("creat error for bar\n");
	exit(0);
}
