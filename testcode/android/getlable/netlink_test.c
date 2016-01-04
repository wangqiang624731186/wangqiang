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


#define UEVENT_BUFFER_SIZE      2048


static int init_hotplug_sock(void)
{

    struct sockaddr_nl snl;
    const int buffersize = 16 * 1024 * 1024;
    int retval;


    memset(&snl, 0x00, sizeof(struct sockaddr_nl));

    snl.nl_family = AF_NETLINK;
    snl.nl_pid = getpid();
    snl.nl_groups = 1;


    int hotplug_sock = socket(AF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);

    if (hotplug_sock == -1)
    {
        printf("error getting socket: %s", strerror(errno));

        return -1;
    }


    /* set receive buffersize */

    setsockopt(hotplug_sock, SOL_SOCKET, SO_RCVBUFFORCE, &buffersize, sizeof(buffersize));
    retval = bind(hotplug_sock, (struct sockaddr *) &snl, sizeof(struct sockaddr_nl));

    if (retval < 0)
    {

        printf("bind failed: %s", strerror(errno));
        close(hotplug_sock);
        hotplug_sock = -1;

        return -1;
    }

    return hotplug_sock;
}



int serach_name(char *buf)
{
    int len = strlen(buf);
    char sendinfo[20];

    memset(sendinfo,0,20);
    if(buf[len-4] == 's'&& buf[len-3] == 'd')
    {
        if(buf[0] == 'a')
        {
            memcpy(sendinfo,"add ",4);
            strcat(sendinfo,buf+len-4);
        }
        else if(buf[0] == 'r')
        {
            memcpy(sendinfo,"remove ",7);
            strcat(sendinfo,buf+len-4);
        }

        printf("sendinfo:%s\n",sendinfo);

    }

    return 1;

}

int  main()
{

    int hotplug_sock  = init_hotplug_sock();

    fd_set readfds;
    int maxfd = hotplug_sock;

    while(1)
    {	char buf[UEVENT_BUFFER_SIZE*2] = {0};
        FD_ZERO(&readfds);
        FD_SET(hotplug_sock, &readfds);
        int fdcount = select(maxfd+1, &readfds, NULL, NULL, NULL);
        if (fdcount < 0) {
            if (errno != EINTR)
                printf("error in select: %s", strerror(errno));
            continue;
        }

        if (FD_ISSET(hotplug_sock, &readfds))
        {
            recv(hotplug_sock, &buf, sizeof(buf), 0);
            serach_name(buf);
            printf("%s\n", buf);
        }
    }

}





