#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <unistd.h> 
void* func(void * data) 
{ 

	char *cmd = (char *)data;
pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); //允许退出线程 
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL); //设置立即取消 
  while (1) 
  {
	printf("11111111111111111111111\n");
	pthread_testcancel();
	printf("22222222222222222222222222\n");
	sleep(100);
	printf("333333333333333333333333\n");
 	pthread_testcancel();
	printf("4444444444444444444444444\n");
	  //操作 ; 
  } 
cmd[0] = 1;
  return NULL; 
} 
int fun() 
{ 
  pthread_t thrd; 
  pthread_attr_t attr; 
  pthread_attr_init(&attr); 
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); 

char cmd[100];
  if( pthread_create(&thrd, &attr, func, (void*)cmd) ) 
  { 
    perror( "pthread_create error "); 
    exit(EXIT_FAILURE); 
   } 
/*   if( !pthread_cancel(thrd) )  
   { 
     printf( "pthread_cancel OK\n " ); 
   } 
  */ 

   return 0; 
} 

int main()
{
	fun();

	sleep(10000);
}
