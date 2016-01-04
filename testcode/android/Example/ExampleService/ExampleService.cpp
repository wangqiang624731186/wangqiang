// File: ExampleService.cpp
#include "ExampleService.h"
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
namespace android {

    static struct sigaction oldact;
    static pthread_key_t sigbuskey;
    
    int ExampleService::instantiate()
    {
        printf("ExampleService instantiate");
        // 调用ServiceManager的addService方法进行系统服务注册，这样客户端程序就可以通过ServiceManager获得此服务的代理对象，从而请求其提供的服务
        int r = defaultServiceManager()->addService(String16("byn.example"), new ExampleService());
        printf("ExampleService r = %d/n", r);
        return r;
    }

    ExampleService::ExampleService()
    { 
        printf("ExampleService created");
        mNextConnId = 1;
        pthread_key_create(&sigbuskey, NULL);
    }

    ExampleService::~ExampleService()
    {
        pthread_key_delete(sigbuskey);
        printf("ExampleService destroyed");
    }
    // 每个系统服务都继承自BBinder类，都应重写BBinder的onTransact虚函数。当用户发送请求到达Service时，系统框架会调用Service的onTransact函数
    status_t ExampleService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
    {
        switch(code)
        {
            case 0: {
	
				/*int i = 0;
				int answer = 0;
		  		data.setDataPosition(0)  ;

				while(data.dataPosition()<data.dataSize())
				{
					data.setDataPosition(i);
					answer = data.readInt32();
					printf("answer:%d",answer);
				}*/
				//data.setDataPosition(0)  ;
				const char *buf = data.readCString(); 	
				        //int num   = data.readInt32();
				//if(buf[0] == 5)
				{
					struct timeval tv;
					struct timezone tz;
		
					gettimeofday(&tv,&tz);
					printf("begin:%d %d",tv.tv_sec,tv.tv_usec);


					reply->writeInt32(100);
					reply->writeInt32(tv.tv_sec);
					reply->writeInt32(tv.tv_usec);
				}

                return NO_ERROR;
                }
                break;
            default:
                return BBinder::onTransact(code, data, reply, flags);
        }
    }
}; //namespace
