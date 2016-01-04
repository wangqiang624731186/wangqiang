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
#include "callback.h"

namespace android{
  int callback::notifyCallback(int a){
    printf("TK---->>>>>>callback.cpp>>>>callback::notifyCallback %d ",a );
				printf("%d\n",getpid());
    return 1;
  }
  status_t callback::onTransact(
        uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags){
    printf("TK---->>>>>>callback.cpp>>>>callback::onTransact");
				printf("%d\n",getpid());
    return Bncallback::onTransact(code, data, reply, flags);
  }
}
