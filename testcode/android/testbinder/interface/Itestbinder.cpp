#include "Itestbinder.h"
#include <binder/Parcel.h>
#include <binder/IInterface.h>
#include <stdio.h>
#include <unistd.h>
#include "Icallback.h"
namespace android{
	  enum {
		TEST_INTERFACE,
		SET_CALLBACK
  };
//////////////////客户端
  class Bptestbinder : public BpInterface<Itestbinder>{
    public:
	      Bptestbinder(const sp<IBinder>& impl) : BpInterface<Itestbinder>(impl){
	      }
      virtual int testinterface(int a){
	        printf("==========================================================\n");
	        printf("TK---->>>>>>Itestbinder.cpp>>>>Bptestbinder::testinterface");
				printf("%d\n",getpid());
        	Parcel data,reply;
       	 data.writeInt32(a);
       	 remote()->transact(TEST_INTERFACE,data,&reply);
       	 return reply.readInt32();
      }
      virtual int setcallback(const sp<Icallback>& callback){
       	printf("==========================================================\n");
        	printf("TK---->>>>>>Itestbinder.cpp>>>>Bptestbinder::setcallback");
				printf("%d\n",getpid());
        	Parcel data, reply;
        	data.writeStrongBinder(callback->asBinder());
        	remote()->transact(SET_CALLBACK, data, &reply);
        	return reply.readInt32();
      }
  };

  IMPLEMENT_META_INTERFACE(testbinder, "android.test.Itestbinder");
/////////////////服务端
  status_t Bntestbinder::onTransact(
  	uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags){
    	printf("TK---->>>>>>Itestbinder.cpp>>>>Bntestbinder::onTransact");
				printf("%d\n",getpid());
    	switch (code) {
      	case TEST_INTERFACE:{
	        	//CHECK_INTERFACE(Itestbinder, data, reply);
	       	printf("TK---->>>>>>Itestbinder.cpp>>>>Bntestbinder::onTransact>>TEST_INTERFACE");
				printf("%d\n",getpid());
	   		reply->writeInt32(testinterface((int) data.readInt32()) );
	        	return NO_ERROR;
      	} break;
      	case SET_CALLBACK:{
		        printf("TK---->>>>>>Itestbinder.cpp>>>>Bntestbinder::onTransact>>SET_CALLBACK");
				printf("%d\n",getpid());
		        sp<Icallback> callback = interface_cast<Icallback>(data.readStrongBinder());
		        //int a = connect(Client);
		        reply->writeInt32(setcallback(callback));    
		        return NO_ERROR;    
     	 }
	      default:{
	        	printf("TK---->>>>>>Itestbinder.cpp>>>>Bntestbinder::onTransact>>333");
				printf("%d\n",getpid());
	        	return BBinder::onTransact(code, data, reply, flags);
	      }
    }
  }
}
