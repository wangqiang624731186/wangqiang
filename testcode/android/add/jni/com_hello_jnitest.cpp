#define LOG_TAG "hello-JNI"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include "jni.h"
#include "JNIHelp.h"
#include <cutils/log.h>
#include <linux/input.h>
#include "android_runtime/AndroidRuntime.h"
static jint com_hello_jnitest_jnitest_nadd(JNIEnv *env, jobject obj, jint a, jint b)
{
	
	struct input_event event;
jint i = open("/dev/input/event2", O_RDWR);
	jint j  = 0;	

	while(1)
	{
		
		sleep(1);	
		if(i>0)
		{
	
			event.type = 3;
			event.code = 53;
			event.value = 497;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);

			event.type = 3;
			event.code = 54;
			event.value = 884;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);


			event.type = 3;
			event.code = 58;
			event.value = 1550;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);


			event.type = 3;
			event.code = 48;
			event.value = 1;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);

			event.type = 3;
			event.code = 57;
			event.value = 0;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);

			event.type = 0;
			event.code = 2;
			event.value = 0;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);

			event.type = 0;
			event.code = 0;
			event.value = 0;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);










			event.type = 3;
			event.code = 53;
			event.value = 497;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);

			event.type = 3;
			event.code = 54;
			event.value = 885;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);


			event.type = 3;
			event.code = 58;
			event.value = 1550;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);


			event.type = 3;
			event.code = 48;
			event.value = 1;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);

			event.type = 3;
			event.code = 57;
			event.value = 0;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);

			event.type = 0;
			event.code = 2;
			event.value = 0;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);

			event.type = 0;
			event.code = 0;
			event.value = 0;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);

			event.type = 0;
			event.code = 2;
			event.value = 0;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);

			event.type = 0;
			event.code = 0;
			event.value = 0;
			j = write(i,&event,sizeof(input_event));
			ALOGE("%d\n",j);

		}
		else
		{
			ALOGE("could open /dev/input/event2\n");
			i = open("/dev/input/event2", O_RDWR);
		}
	}
	return (a + b);
}

static JNINativeMethod gMethods[] = {
	{"nadd", "(II)I", (void *)com_hello_jnitest_jnitest_nadd},
};

static int register_android_test_hello(JNIEnv *env)
{
	return android::AndroidRuntime::registerNativeMethods(env, "com/hello/jnitest/Nadd", gMethods, NELEM(gMethods));
}
jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	JNIEnv *env = NULL;
	if (vm->GetEnv((void **)&env, JNI_VERSION_1_4) != JNI_OK) {
		printf("Error GetEnv\n");
		return -1;
	}
	assert(env != NULL);
	if (register_android_test_hello(env) < 0) {
		printf("register_android_test_hello error.\n");
		return -1;
	}
	return JNI_VERSION_1_4;
}
