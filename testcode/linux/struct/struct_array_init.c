/*************************************************************************
	> File Name: struct_array_init.c
	> Author: wangqiang
	> Mail: 624731186@qq.com 
	> Created Time: 2016年01月04日 星期一 11时19分42秒
 ************************************************************************/

#include<stdlib.h>
#include<stdio.h>

typedef struct{
    char a;
    char b;
    char c;
    char data[8];
    char describe[32];
}struct_array_init_1;

struct_array_init_1 array_test[]={
{0x01,0x02,0x033,4,16,0,0,0,0,0,0,"test1"},
{0x11,2,3,4,5,4,0,0,0,0,0,"test2"},
};

int main()
{
    printf("%x\n",array_test[0].a);
    printf("%x\n",array_test[0].b);
    printf("%x\n",array_test[0].c);
    printf("%x %x %x %x %x %x %x %x\n",
           array_test[0].data[0],
           array_test[0].data[1],
           array_test[0].data[2],
           array_test[0].data[3],
           array_test[0].data[4],
           array_test[0].data[5],
           array_test[0].data[6],
           array_test[0].data[7]
          );

    printf("%s\n",array_test[0].describe);
    
    
    printf("%x\n",array_test[1].a);
    printf("%x\n",array_test[1].b);
    printf("%x\n",array_test[1].c);
    printf("%x %x %x %x %x %x %x %x\n",
           array_test[1].data[0],
           array_test[1].data[1],
           array_test[1].data[2],
           array_test[1].data[3],
           array_test[1].data[4],
           array_test[1].data[5],
           array_test[1].data[6],
           array_test[1].data[7]
          );

    printf("%s\n",array_test[1].describe);
}
