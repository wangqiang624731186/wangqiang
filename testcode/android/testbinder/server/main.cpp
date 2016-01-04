#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include <stdio.h>
#include <unistd.h>
#include "testbinder.h"


using namespace android;

int main(int argc, char** argv)
{
  sp<ProcessState> proc(ProcessState::self());
  sp<IServiceManager> sm = defaultServiceManager();

  printf("ServiceManager: %p", sm.get());
printf("%d\n",getpid());


  testbinder::instantiate();

  ProcessState::self()->startThreadPool();



  IPCThreadState::self()->joinThreadPool();
  return 0;
}
