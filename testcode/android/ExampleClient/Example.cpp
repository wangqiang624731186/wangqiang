// File: Example.cpp
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include "Example.h"
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <cutils/log.h>


#define  LOG_TAG  		"wangq"
namespace android
{
    sp<IBinder> binder;
    void Example::add100(int n)
    {
        getExampleService();
        Parcel reply;
        int answer;
		Parcel data[10]  ;  
 
	int i = 0;
	char buf[1024*100];
	
	while(i < 1024 *100)
	{
		buf[i] = i;
		if(buf[i] == 0)
		{
			buf[i] = 1;
		}
		//printf("i:%d,buf[i]:%d",i,buf[i]);
		i++;
	}
		struct timeval tv;
		struct timezone tz;
		
		gettimeofday(&tv,&tz);
		printf("begin:%d %d",tv.tv_sec,tv.tv_usec);
		int answer1;
		int answer2;

		i = 0;
			char buf1[10];
			data[i].writeCString(buf1);
        	
			gettimeofday(&tv,&tz);
			ALOGE("----------------------client begin:%d %d",tv.tv_sec,tv.tv_usec);	
			binder->transact(0, data[i], &reply);		

        	answer = reply.readInt32();
			answer1 = reply.readInt32();
			answer2 = reply.readInt32();
        	printf("answner=%d end:%d %d\n", answer,answer1,answer2);

	/*	i = 0;
		for(i=0;i<10;i++)
		{
			buf[0] =i+1;
			buf[1024 *100-1] =i+1;
			data[i].writeCString(buf);
        	binder->transact(0, data[i], &reply);		

        	answer = reply.readInt32();
			answer1 = reply.readInt32();
			answer2 = reply.readInt32();
        	printf("answner=%d end:%d %d\n", answer,answer1,answer2);
		}
	*/




		/*buf[0] =2;
		buf[1024 *100-1] =2;
		data1.writeCString(buf);
        printf("BpExampleService::create remote()->transact()/n");
        binder->transact(0, data2, &reply);

        answer = reply.readInt32();
		answer1 = reply.readInt32();
		answer2 = reply.readInt32();
        printf("answner=%d end:%d %d\n", answer,answer1,answer2);

		buf[0] =3;
		buf[1024 *100-1] =3;
		data1.writeCString(buf);
        printf("BpExampleService::create remote()->transact()/n");
        binder->transact(0, data3, &reply);

        answer = reply.readInt32();
		answer1 = reply.readInt32();
		answer2 = reply.readInt32();
        printf("answner=%d end:%d %d\n", answer,answer1,answer2);

		buf[0] =4;
		buf[1024 *100-1] =4;
		data1.writeCString(buf);
        printf("BpExampleService::create remote()->transact()/n");
        binder->transact(0, data4, &reply);

        answer = reply.readInt32();
		answer1 = reply.readInt32();
		answer2 = reply.readInt32();
        printf("answner=%d end:%d %d\n", answer,answer1,answer2);

		buf[0] =5;
		buf[1024 *100-1] =101;
		data1.writeCString(buf);
        printf("BpExampleService::create remote()->transact()/n");
        binder->transact(0, data5, &reply);


        answer = reply.readInt32();
		answer1 = reply.readInt32();
		answer2 = reply.readInt32();
        printf("answner=%d end:%d %d\n", answer,answer1,answer2);  */


        return;
    }

    const void Example::getExampleService()
    {
        sp<IServiceManager> sm = defaultServiceManager();
        binder = sm->getService(String16("byn.example"));
        printf("Example::getExampleService %p/n",sm.get());
        if (binder == 0) {
            printf("ExampleService not published, waiting...");
        return;
        }
    }
}; //namespace

using namespace android;

int main(int argc, char** argv)
{
    Example* p = new Example();
    p->add100(1);
    return 0;
}

