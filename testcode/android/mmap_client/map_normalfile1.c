#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>



void main(int argc, char** argv) // map a normal file as shared mem:
{
	int fd,i;
	char *buf;
	char temp;
	char writebuf[1024*1024];
	fd=open("/data/mmap_test",O_CREAT|O_RDWR|O_TRUNC,00777);
	lseek(fd,1024*1024-1,SEEK_SET);

	write(fd,"",1);

	buf = (char*) mmap( NULL,1024*1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0 );
	close( fd );
	temp = 'a';
	i = 0;
	while(i < 1024 *1024)
	{
		writebuf[i] = i;
		if(writebuf[i] == 0)
		{
			writebuf[i] = 1;
		}
		//printf("i:%d,buf[i]:%d",i,buf[i]);
		i++;
	}
	writebuf[1024*1024-1] = 100;
		struct timeval tv;
		struct timezone tz;
		
		gettimeofday(&tv,&tz);
		printf("begin:%d %d",tv.tv_sec,tv.tv_usec);

	memcpy(buf,writebuf,1024*1024);

	printf(" initialize over \n");
	sleep(100);

	munmap( buf, 1024*1024);
	printf( "umap ok \n" );
}
