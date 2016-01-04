
	#include <stdlib.h> 
	#include <sys/types.h>
	#include <stdio.h> 
	#include <sys/socket.h> 
	#include <netinet/in.h> 
	#include <string.h> 
	int main() 
	{ 
		int sfp,nfp; 
		struct sockaddr_in s_add,c_add;
		int sin_size; 
		unsigned short portnum=5050; 
		printf("Welcome to my server !\r\n"); 

		sfp = socket(AF_INET, SOCK_STREAM, 0); 
		if(-1 == sfp) { 
			printf("server socket fail ! \r\n"); 
			return -1; 
		} 
		printf("server socket ok !\r\n"); 
		bzero(&s_add,sizeof(struct sockaddr_in)); 
		s_add.sin_family=AF_INET; 
		s_add.sin_addr.s_addr=htonl(INADDR_ANY); 
		s_add.sin_port=htons(portnum); 

	if(-1 == bind(sfp,(struct sockaddr *)(&s_add), sizeof(struct sockaddr))) { 
			printf("server bind fail !\r\n"); 
			return -1; 
		} 
		printf("server bind ok !\r\n"); 
	if(-1 == listen(sfp,5)) { 
			printf("server listen fail !\r\n"); 
			return -1; 
		} 
		printf("server listen ok\r\n"); 
		

	while(1) { 
		sin_size = sizeof(struct sockaddr_in); 
	nfp = accept(sfp, (struct sockaddr *)(&c_add), &sin_size); 
		if(-1 == nfp) {
			 printf("server accept fail !\r\n"); 
			return -1; 
		}
		 printf("server accept ok!\r\nServer start get connect from %#x : %#x\r\n",ntohl(c_add.sin_addr.s_addr),ntohs(c_add.sin_port)); 
	if(-1 == write(nfp,"client,welcome to my server \r\n",32)) { 
			printf("server write fail!\r\n"); 
			return -1; 
		} printf("server write ok!\r\n"); 
		close(nfp); 
		}


		 close(sfp); 
		return 0;
	 }
