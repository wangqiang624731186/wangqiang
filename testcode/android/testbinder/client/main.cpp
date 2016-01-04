#include <stdio.h>
#include <unistd.h>
#include "client.h"
#include "callback.h"

using namespace android;

int main(int argc, char* argv[]){
  client* myclient = new client();
  if(myclient == NULL) return 0;
  const sp<Itestbinder>& tb = myclient->get_test_binder();
  if(tb == NULL) return 0;
  sp<callback> c = new callback();
  int a = tb->setcallback(c);
 a = tb->testinterface(3);
 a = tb->testinterface(4);
  printf("TK-------->>>result is %d",a);
				printf("%d\n",getpid());

  ProcessState::self()->startThreadPool();
  IPCThreadState::self()->joinThreadPool();
  delete myclient;
  return 0;
}
