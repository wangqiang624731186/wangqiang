#include <stdio.h>
int main(int argc,char **argv)
{
	if(argc !=2)
	{
		printf("invalid parameter!\n");
		return ;
	}
	
	char *strP = argv[1];
	int specSize = atoi(strP);
	if(specSize <= 0 )
	{
		printf("invalid parameter!\n");
		return ;
	}

	char *pmem[4096] = {0};
	const int fragSize = 1024*1024*1; //1M
	memset(pmem,0x0,4096);
	int index = 0;
	int totalAlloced = 0;
	while(index < 4096 && totalAlloced < specSize)
	{
		pmem[index] = (char *)malloc(fragSize);
		if(pmem[index])
		{
			totalAlloced ++;
			printf("allocated mem:1M success, address:%p ,total allocated:%d M\n",pmem[index],totalAlloced);
			memset(pmem[index],0xA5,fragSize);
			system("free -m |grep \"Mem:\"");
		}
		else
		{
			printf("allocation failed!\n");
			return 0;
		}
		index++;
		printf("\n");
		//usleep(200);
	}
	return 0;
}
