#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

void main(int argc, char** argv) // map a normal file as shared mem:
{
	int fd,i;
	char  *buf;
	fd=open("/data/mmap_test",O_CREAT|O_RDWR,00777 );
	buf = (char *)mmap(NULL,1024*1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

	
while(1)
{
if(buf[1024*1024-1] == 100)
	{
	printf( "name: %d \n",buf[1024*1024-1]);
	struct timeval tv;
		struct timezone tz;
		
		gettimeofday(&tv,&tz);
		printf("end:%d %d",tv.tv_sec,tv.tv_usec);
	}
}
 munmap( buf,1024*1024 );
return;
}
