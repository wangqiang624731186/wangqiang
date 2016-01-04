/*************************************************************************
	> File Name: test.c
	> Author: wangqiang
	> Mail: wangqiang.neu@neusoft.com 
	> Created Time: Fri 16 Jan 2015 04:15:48 PM CST
 ************************************************************************/

#include<stdlib.h>

#include<stdio.h>
void bin( int value, int bytes, char *bitmap )
 {
         int i;
 
         bitmap[0] =0;
         for( i=( bytes * 8 - 1 ); i>=0; i-- ){
                 strcat( bitmap, ( value & ( 1 << i  ) )  ? "1 " : "0 " );
         }
 }
 
 int main(int argc,char** argv)
 {
 	 char bitmap[1024];
 	 memset(bitmap,0,1024);
 	 int value = 0;
 	 sscanf( argv[1], "%x", &value );
	 printf("value:%d\n",value);
 	 bin(value,4,bitmap);
 	 printf("%s\n",bitmap);
 	 
 	 return 1;
 }
