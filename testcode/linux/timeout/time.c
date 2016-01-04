#include <setjmp.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>



extern volatile int invoke_count;
extern sigjmp_buf invoke_env;

void timeout_signal_handler(int sig);
typedef void sigfunc(int sig);
sigfunc *my_signal(int signo, sigfunc* func);
#define E_CALL_TIMEOUT (-9)

#define add_timeout_to_func(func, n, interval, ret, ...) \
    { \
        invoke_count = 0; \
        sigfunc *sf = my_signal(SIGALRM, timeout_signal_handler); \
        if (sf == SIG_ERR) { \
            ret = errno; \
            goto end; \
        }  \
\
        if (sigsetjmp(invoke_env, SIGALRM) != 0) { \
            if (invoke_count >= n) { \
                ret = E_CALL_TIMEOUT; \
                goto err; \
            } \
        } \
\
        alarm(interval); \
		printf("%d %s %d\n",__VA_ARGS__);\
        ret = func(__VA_ARGS__);\
		printf("%d %s %d\n",__VA_ARGS__);\
        alarm(0); \
err:\
        my_signal(SIGALRM, sf); \
end:\
        ;\
    }

/* timeout_wrapper.c */

volatile int invoke_count = 0;
sigjmp_buf invoke_env;

void
timeout_signal_handler(int sig)
{
    invoke_count++;
    siglongjmp(invoke_env, 1);
}

sigfunc *
my_signal(int signo, sigfunc *func)
{
    struct sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    } else {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;
#endif
    }
    if (sigaction(signo, &act, &oact) < 0)     
	{
		printf("11111111111111111111111\n");
		return SIG_ERR;

	}
    return oact.sa_handler;
}


int
main()
{
    #define MAXLINE 1024
    char line[MAXLINE];

    int ret = 0;
    int try_times = 10;
    int interval = 1000;
    add_timeout_to_func(printf, try_times, interval, ret, STDIN_FILENO, line, MAXLINE);
    if (ret == E_CALL_TIMEOUT) {
        printf("invoke read timeouts for 3 times\n");
        return -1;
    } else if (ret == 0) {
        printf("invoke read ok\n");
        return 0;
    } else {
        printf("add_timeout_to_func error = %d\n", ret);
    }

	sleep(10);
}
