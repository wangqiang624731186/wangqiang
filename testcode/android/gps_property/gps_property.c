#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <cutils/log.h>
#include <cutils/sockets.h>
#include <cutils/properties.h>

static char   prop[512];

int main(int argc, char* argv[])
{

	// look for a kernel-provided device name
	if (property_get("athr.gps.mode",prop,"hosted") == 0)
	{
		printf("Running ATHR GPS driver in hosted mode! %s\n",prop);
		if (property_get("athr.gps.node",prop,"") == 0)
		{
			printf("no user specific gps device name... try default name... %s\n",prop);
			if (property_get("ro.kernel.android.gps",prop,"") == 0)
			{
				printf("no kernel-provided gps device name (hosted)  %s\n",prop);
				printf("please set ro.kernel.android.gps property");
				return 1;
			}
		}
	}
	else
	{
		if (property_get("ro.kernel.android.gps",prop,"") == 0)
		{
			printf("no kernel-provided gps device name (not hosted) %s\n",prop);
			printf("please set ro.kernel.android.gps property");
			return 1;
		}
	}

	printf("prop %s\n",prop);
	return 1;
}





