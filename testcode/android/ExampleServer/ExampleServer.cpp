// File: ExampleServer.cpp
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include <private/android_filesystem_config.h>
#include "../ExampleService/ExampleService.h"

using namespace android;

int main(int argc, char** argv)
{
    sp<ProcessState> proc(ProcessState::self());	// 要想使用Binder机制，必须要创建一个ProcessState对象
    sp<IServiceManager> sm = defaultServiceManager();
    printf("ServiceManager: %p", sm.get());
    ExampleService::instantiate();
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
