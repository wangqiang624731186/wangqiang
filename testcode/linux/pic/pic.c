#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>



void main(int argc,char** argv)
{

	int fd = open(argv[1],O_RDONLY);
	if(fd < 0)
	{
		printf("open %s failed\n",argv[1]);
	}

	int bytes = lseek(fd , 0 , SEEK_END);
	int count = (bytes -54)/3;
	lseek(fd , 0 , SEEK_SET);

	char path[255];
	memset(path,0,255);
	strncpy(path,argv[1],strlen(argv[1])-4);
	strncat(path,"_new.bmp",8);

	printf("file:%s\n",path);
	int fd_new = open(path,O_RDWR|O_CREAT,S_IRWXU);
	if(fd_new < 0)
	{
		printf("create %s failed\n",path);
	}
	
	char content[255];
	read(fd,content,54);
	write(fd_new,content,54);

	int i = 0;
	for(i = 0; i < count; i++)
	{
		read(fd,content,3);
		write(fd_new,0,1);
		write(fd_new,content,3);
	}

	close(fd);
	close(fd_new);

	return ;
}
