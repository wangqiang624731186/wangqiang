#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

static void show_event(struct input_event* event)
{
        printf("%d %d %d", event->type, event->code, event->value);

        return;
}

int main(int argc, char* argv[])
{
        struct input_event event;

        int fd = open(argv[1], O_RDWR);

        if(fd > 0 )
        {
			while(1)
			{
				usleep(100000); 
				printf("%s:",argv[1]);
				if(read(fd, &event, sizeof(event))== sizeof(event))
				{
					
					show_event(&event);
				}
				printf("\n");
			}
        }

        return 0;
}




