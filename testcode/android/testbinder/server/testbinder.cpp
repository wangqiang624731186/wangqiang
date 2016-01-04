#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
//#include <utils/Trace.h>
#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <utils/String16.h>
#include <utils/threads.h>
#include <utils/Atomic.h>
#include <stdio.h>
#include <unistd.h>
//#include <cutils/bitops.h>
#include <cutils/properties.h>
#include <cutils/compiler.h>
#include "testbinder.h"

namespace android{
  int testbinder::testinterface(int a){
    printf("TK---->>>>>>testbinder.cpp>>>>testbinder::testinterface ");
printf("%d\n",getpid());
    sp<Icallback> c = mcallback;
    c->notifyCallback(2);
    c->notifyCallback(4);
    return a+2;
  }
  int testbinder::setcallback(const sp<Icallback>& callback){
    printf("TK---->>>>>>testbinder.cpp>>>>testbinder::setcallback");
printf("%d\n",getpid());
    mcallback = callback;
    return 1;
  }
  status_t testbinder::onTransact(
        uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags){
    printf("TK---->>>>>>testbinder.cpp>>>>testbinder::onTransact");
printf("%d\n",getpid());
    return Bntestbinder::onTransact(code, data, reply, flags);
  }
}
