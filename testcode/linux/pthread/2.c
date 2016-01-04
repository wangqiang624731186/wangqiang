#include <pthread.h>
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* thread0(void* arg)
{
    pthread_mutex_lock(&mutex);
    printf("in thread 0 tag 1\n");
    pthread_cond_wait(&cond, &mutex);
    printf("in thread 0 tag 2\n");
    pthread_mutex_unlock(&mutex);
    printf("in thread 0 tag 3\n");
    pthread_exit(NULL);
}

void* thread1(void* arg)
{
    sleep(10);
    printf("in thread 1 tag 1\n");
    pthread_mutex_lock(&mutex);
    printf("in thread 1 tag 2\n");
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
    printf("in thread 1 tag 3\n");
    pthread_exit(NULL);
}
int main()
{
    pthread_t tid[2];
    if (pthread_create(&tid[0], NULL, thread0, NULL) != 0) 
    {
        exit(1);
    }
    if (pthread_create(&tid[1], NULL, thread1, NULL) != 0) 
    {
        exit(1);
    }
    sleep(5);
    printf("in main thread tag 1\n");
    pthread_cancel(tid[0]);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
