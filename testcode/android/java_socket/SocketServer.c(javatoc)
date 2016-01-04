#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <stddef.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

#define SOCKET_PATH "/data/file_socket"
#define BUF_LENGTH  1024*1024

static int client[FD_SETSIZE];
static int maxi;

/***************************************
*
*****************************************/
static void set_sock_nonblock(int sock) {
	int flags;
	flags = fcntl(sock, F_GETFL, 0);
	if (flags < 0) {
		perror("fcntl(F_GETFL) failed");
		exit(EXIT_FAILURE);
	}
	if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0) {
		perror("fcntl(F_SETFL) failed");
		exit(EXIT_FAILURE);
	}
}




/***************************************
*
*****************************************/

int main () {

	struct sockaddr_un sin;
	struct sockaddr_un pin;
	int listen_fd;
	int conn_fd;
	int sock_fd;
	int nready;
	fd_set allset;
	int address_size;
	char buf[BUF_LENGTH];
	int i;
	int n;
	int len;
	int opt =1;
	int save_flags;
	pthread_t pid;
        int maxfd;
	fd_set rset;
	
	signal(SIGPIPE,SIG_IGN);
	
	bzero(&sin,sizeof(sin));

	sin.sun_family = AF_UNIX; 
	strcpy(sin.sun_path, SOCKET_PATH);

	listen_fd = socket(PF_UNIX, SOCK_STREAM, 0);
	if (-1 == listen_fd) {
		perror("call to socket\n");
		exit(EXIT_FAILURE);
	}

	set_sock_nonblock(listen_fd);

	unlink(SOCKET_PATH);

	n = bind (listen_fd,(struct sockaddr*)&sin,sizeof(sin));
	if ( -1 == n) {
		perror("call to bind\n");
		exit(EXIT_FAILURE);
	}

	n = listen(listen_fd,FD_SETSIZE);
	if ( -1 == n) {
		perror("call to listen\n");
		exit(EXIT_FAILURE);
	}

	printf("Acceping connections ... \n");

	maxfd = listen_fd;
	maxi  = -1;

	for (i = 0; i < FD_SETSIZE; i++) {
		client[i] = -1;
	}

	FD_ZERO(&allset);
	FD_SET(listen_fd,&allset);


	for(;;)
	{
		rset = allset;
		nready = select(maxfd+1,&rset,NULL,NULL,NULL);
		if (FD_ISSET(listen_fd,&rset)) 
		{
			address_size = sizeof(pin);
g_eintr2:		
	conn_fd = accept(listen_fd,(struct sockaddr *)&pin,&address_size);
			if ( (-1 == conn_fd)) {

					if (errno == EAGAIN/*Resource temporarily unavailable*/ ||
							errno == EWOULDBLOCK ||
							errno == ECONNABORTED ||
							errno == EPROTO )
						continue;
					else if (errno == EINTR/*Interrupted system call*/)
						goto g_eintr2;
					else
						printf("accept  error \n");
		}

			set_sock_nonblock(conn_fd);

			if (maxi < FD_SETSIZE) 	{
				for ( i = 0; i <FD_SETSIZE; i++) {
					if (client[i] < 0 ) {
						client[i] = conn_fd;
						break;
					}
				}
			}else {
				printf("too many clients \n");
			}
			printf("new client: %d  client: %d \n",conn_fd,i);
			if ( i == FD_SETSIZE){
				printf(" clients count = FD_SETSIZE\n ");
			}

			FD_SET(conn_fd,&allset);

			if (conn_fd > maxfd ) 
				maxfd = conn_fd;
			if (i > maxi)
				maxi = i;
			printf("nready:%d\n",nready);
			//if (--nready <= 0)
			//	continue;
		
		}

		for ( i = 0; i <= maxi; i++) {

			if ((sock_fd = client[i]) < 0 )
				continue;
			if (FD_ISSET(sock_fd,&rset)){

g_eintr3:
				
				n = read(sock_fd,buf,BUF_LENGTH);
				buf[100] = 0;
				if(n<100)
				{
					printf("begin:%s\n",buf);
				}

				printf("11111111111111111111111:%d\n",n);
				
					struct timeval tv;
					struct timezone tz;
		
					gettimeofday(&tv,&tz);
					printf("end:%d %d",tv.tv_sec,tv.tv_usec);

				
				
			}
		}

	}
}

