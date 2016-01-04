# include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/time.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

void main(int argc, char** argv) // map a normal file as shared mem:
{

	DIR *dir = NULL;
	struct dirent *ptr = NULL;	
	dir = opendir("/sys/power");
	int fd = 0;
	
	while(1)
	{
		printf("===================================\n");
		while((ptr = readdir(dir)) != NULL)
		{
			printf("%s\n",ptr->d_name);
			fd = 0;
			char buf[256];
			memset(buf,0,256);
			sprintf(buf,"/sys/power/%s",ptr->d_name);
			fd = open(buf,O_WRONLY);
			char buf2[256];
			memset(buf2,0,256);
			read(fd,buf2,256);
			printf("%s\n",buf2);
			close(fd);
		}
		sleep(1);
	}
return;
}
