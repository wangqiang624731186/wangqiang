
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <utime.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <cutils/fs.h>
#include <cutils/sockets.h>
#include <cutils/log.h>
#include <cutils/properties.h>
#include <cutils/multiuser.h>

#include <private/android_filesystem_config.h>
#include <sys/capability.h>
#include <linux/prctl.h>

//#include "installd.h"


#define BUFFER_MAX 1024

int main(const int argc, const char *argv[]) {
    char buf[BUFFER_MAX];
    struct sockaddr addr;
    socklen_t alen;
    int lsocket, s, count;

    printf("installd firing up\n");
	sprintf(buf,"1232342345345\n");


    lsocket = android_get_control_socket("myserver");
    if (lsocket < 0) {
        printf("Failed to get socket from environment: %s\n", strerror(errno));
        exit(1);
    }
    if (listen(lsocket, 5)) {
        printf("Listen on socket failed: %s\n", strerror(errno));
        exit(1);
    }
    fcntl(lsocket, F_SETFD, FD_CLOEXEC);

    for (;;) {
        alen = sizeof(addr);
        s = accept(lsocket, &addr, &alen);
        if (s < 0) {
            printf("Accept failed: %s\n", strerror(errno));
            continue;
        }
        fcntl(s, F_SETFD, FD_CLOEXEC);

        printf("new connection\n");
        for (;;) {
            unsigned short count;
			
			write(s,buf,1024);
 			sleep(1);
        }
        printf("closing connection\n");
        close(s);
    }

    return 0;
}
