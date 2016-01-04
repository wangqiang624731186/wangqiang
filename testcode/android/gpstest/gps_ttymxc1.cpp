
#include <errno.h>
#include <pthread.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <math.h>
#include <time.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/inotify.h>
#include <poll.h>

#define  LOG_TAG  "athr_gps"

#include <cutils/log.h>
#include <cutils/sockets.h>
#include <cutils/properties.h>
int main()
{

	
    int fd = open("/dev/ttymxc1", O_RDWR | O_NOCTTY | O_NONBLOCK);
	if ( isatty( fd ) ) {
        struct termios  ios;
        tcgetattr( fd, &ios );
        bzero(&ios, sizeof(ios));
        ios.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
        ios.c_iflag = IGNPAR;
        ios.c_oflag = 0;
       // ios.c_lflag = 0;  /* disable ECHO, ICANON, etc... */
        tcsetattr( fd, TCSANOW, &ios );
		tcflush(fd,TCIOFLUSH);
    }

	char buf[256];
	while(1)
    {
        usleep(1000);
		read( fd, buf, 256 );
		printf("%s",buf);
    }

    return 0;
}
