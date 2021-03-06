/*******************************************************************************
\file          lseek.c
\author        wangqiang
\mail          wangqiang@auto-link.com
\version       0.1
\date          2016-04-12 09:03
*******************************************************************************/

/*******************************************************************************
Include Files
*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*******************************************************************************
Type Definition
*******************************************************************************/

/*******************************************************************************
Function  Definition
*******************************************************************************/



int main()
{
    int fp = open("./data",O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
    write(fp,"1234567890",10);
    printf("%d\n",lseek(fp,0,SEEK_CUR));
    return 0;
}
