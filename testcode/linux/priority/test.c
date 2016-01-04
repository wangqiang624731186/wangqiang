#include<stdlib.h>
#include<stdio.h>
#include<sys/time.h>
#include<sys/resource.h>

int main()
{
	int ret;
	struct sched_param sp ;
	sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
	printf("sched_get_priority_max:%d\n" ,sp.sched_priority);
	ret = sched_setscheduler(0 , SCHED_FIFO,&sp);
	if(ret == -1)
	{
		perror("sched_setscheduler");
	}
	while(1)
	{
		sleep(1);
	}

}
