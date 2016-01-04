#include <sys/un.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "dd.h"

static int wangq_fd = -1;

int main()
{
	char ddstring[7][50] = {"dd\0","if=/u-boot.bin\0","of=/dev/block/mmcblk0boot0\0","bs=512\0","seek=2\0","skip=2\n","\n"};
/*
	char buf[100];
	int a = open("/system/123",O_CREAT | O_WRONLY, S_IRWXU);
	if(a>0)
	{
		write(a,"1",1);
	}

	wangq_fd = a;*/
	char *test[7];
	int i = 0;
	while(i<6)
	{
		test[i] = malloc(strlen(ddstring[i])+1);
		memcpy(test[i],ddstring[i],strlen(ddstring[i])+1);
		i++;
	}
	int fd = open("/sys/block/mmcblk0boot0/force_ro",O_WRONLY);

/*
	memset(buf,100,0);
	sprintf(buf,"fd=%d\n",fd);
	write(a,buf,strlen(buf));*/
	printf("fd=%d\n",fd);
	if(fd>0)
	{	
		int b = write(fd,"0",1);
	/*	memset(buf,100,0);
		sprintf(buf,"write=%d\n",b);
		write(a,buf,strlen(buf));
*/
		printf("write=%d\n",b);
		//system("/system/bin/dd if=/u-boot.bin of=/dev/block/mmcblk0boot0 bs=512 seek=2 skip=2");
		dd(6,test);
	
		b = write(fd,"1",1);
/*		memset(buf,100,0);
		sprintf(buf,"write=%d\n",b);
		write(a,buf,strlen(buf));
*/
		printf("write=%d\n",b);
		close(fd);
	}

	
	fd = open("/sys/devices/platform/sdhci-esdhc-imx.3/mmc_host/mmc0/mmc0:0001/boot_config",O_WRONLY);

	printf("fd=%d\n",fd);
	if(fd>0)
	{
		printf("write=%d\n",write(fd,"8",1));
		close(fd);
	}

	system("sync");
	return 0;
}




