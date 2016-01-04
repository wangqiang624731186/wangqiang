#include <stdio.h>
#include <pthread.h>
#include <sys/prctl.h>

void* callcbk(void *arg)
{
	while(1)
	{
		sleep(1);
	}
}
void *foo(void *arg)
{
	int idx = arg;
	printf("idx = %d\n", idx);
	switch(idx)
	{
		case 1:
		prctl(PR_SET_NAME, "ThreadName1");
		break;
		case 2:
		prctl(PR_SET_NAME, "ThreadName2");
		break;
		case 3:
		prctl(PR_SET_NAME, "ThreadName3");
		break;
		default:
		break;
	}

	pthread_t threadIdx;
	pthread_create(&threadIdx, NULL,callcbk , NULL);
	pthread_join(threadIdx, NULL);

	sleep(50);
	return 0;
}

int main(void)
{
	pthread_t threadIdx[3];
	int threadArgIdx[] = {1, 2, 3};
	
	int i;
	for(i = 0; i < 3; i++)
	{
		pthread_create(threadIdx + i, NULL, foo, (void *)threadArgIdx[i]);
	}

	for(i = 0; i < 3; i++)
	{
		pthread_join(threadIdx[i], NULL);
	}

	sleep(60);
	return 0;
}
