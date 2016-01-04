#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <apue.h>

int                 anaFlag = 0; //The flag of analysis
sigset_t            mask;
pthread_mutex_t		anaFlag_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t      anaFlag_signal = PTHREAD_COND_INITIALIZER;

	void *
sig_handler(void *arg)
{
	int err, signo;
	for (;;) {
		err = sigwait(&mask, &signo);
		if (err != 0)
			err_exit(err, "sigwait failed");
		switch (signo) {
			case SIGUSR1:
				pthread_mutex_lock(&anaFlag_lock);
				anaFlag = 1;
				pthread_mutex_unlock(&anaFlag_lock);
				pthread_cond_signal(&anaFlag_signal);
				break;
			case SIGUSR2:
				pthread_mutex_lock(&anaFlag_lock);
				anaFlag = 0;
				pthread_mutex_unlock(&anaFlag_lock);
				pthread_cond_signal(&anaFlag_signal);
				break;
			default:
				err_sys("unexpected signal %d\n", signo);
		}
	}
}

	int
main(void)
{
	int   ret;
	pthread_t  signalTid;

	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigaddset(&mask, SIGUSR2);
	if ((ret = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0)
		err_exit(ret, "SIG_BLOCK error");
	if ((ret = pthread_create(&signalTid, NULL, sig_handler, 0)) != 0)
		err_exit(ret, "can't create thread");

	pthread_mutex_lock(&anaFlag_lock);
	printf("befor analysis, wait signal, anaFlag=%d\n", anaFlag);
	while (anaFlag == 0)
		pthread_cond_wait(&anaFlag_signal, &anaFlag_lock);
	pthread_mutex_unlock(&anaFlag_lock);

	/* analyse something... */
	printf("analysis start, anaFlag=%d\n",anaFlag);

	pthread_mutex_lock(&anaFlag_lock);
	while (anaFlag == 1){
		pthread_cond_wait(&anaFlag_signal, &anaFlag_lock);
	}
	pthread_mutex_unlock(&anaFlag_lock);

	/* after analysis */
	printf("after analysis, wait signal, anaFlag=%d\n",anaFlag);

	/* deal with the result ... */

	exit(0);
}
