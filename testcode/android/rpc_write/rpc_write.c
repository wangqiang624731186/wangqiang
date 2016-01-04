#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char* argv[])
{
        struct input_event event;

        int fd = open(argv[1], O_RDWR);

		if(fd > 0 ){

			int code = atoi(argv[2]);
			int state = atoi(argv[3]);
			ioctl(fd,code, &state);
			ioctl(fd,code, &state);
			printf("sucess\n");
			close(fd);
		}else
		{
			printf("failed\n");
		}

        return 0;
}




