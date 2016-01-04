#include <sys/un.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <string.h>
#include <linux/netlink.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>



int  main()
{

	system("am start -n com.android.settings/.Settings");

	return 1;
}





