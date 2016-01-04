// File: Example.cpp
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <utils/String8.h>

using namespace android;

int main(int argc, char** argv)
{
	sp<IServiceManager> sm = defaultServiceManager();
	Vector<String16> services = sm->listServices();
	printf("services size:%d\n",services.size());

	for (unsigned i = 0; i < services.size(); i++) {
		String16 name = services[i];
		sp<IBinder> service = sm->checkService(name);
		String8 svc(name);
		//String8 svc(name);
		printf("i:%d svc.string:%s\n",i,svc.string());
 	}

    return 0;
}

