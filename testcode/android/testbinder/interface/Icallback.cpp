#include "Itestbinder.h"
#include <binder/Parcel.h>
#include <binder/IInterface.h>
#include <stdio.h>
#include <unistd.h>
namespace android{
	  enum {
	    	NOTIFY_CALLBACK,
	  };
//////////////////客户端
	  class Bpcallback : public BpInterface<Icallback>{
	    public:
		      Bpcallback(const sp<IBinder>& impl) : BpInterface<Icallback>(impl){
		      }
		      virtual int notifyCallback(int a){
			        printf("==========================================================\n");
			        printf("TK---->>>>>>Icallback.cpp>>>>Bpcallback::notifyCallback");
				printf("%d\n",getpid());
			        Parcel data,reply;
			        data.writeInt32(a);
			        remote()->transact(NOTIFY_CALLBACK,data,&reply);
			        return reply.readInt32();
		      }
	  };

  IMPLEMENT_META_INTERFACE(callback, "android.test.Icallback");
/////////////////服务端
  status_t Bncallback::onTransact(
	      uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags){
	    	printf("TK---->>>>>>Icallback.cpp>>>>Bncallback::onTransact");
		printf("%d\n",getpid());
		    switch (code) {
			      case NOTIFY_CALLBACK:{
			        //CHECK_INTERFACE(Itestbinder, data, reply);
			        printf("TK---->>>>>>Icallback.cpp>>>>Bncallback::onTransact>>NOTIFY_CALLBACK");
				printf("%d\n",getpid());
			        reply->writeInt32(notifyCallback((int) data.readInt32()) );
			        return NO_ERROR;
		      } break;
		      default:{
			        printf("TK---->>>>>>Icallback.cpp>>>>Bncallback::onTransact>>222");
				printf("%d\n",getpid());
			        return BBinder::onTransact(code, data, reply, flags);
		      }
		    }
	  }
}
