#define LOG_TAG "hellojni"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <assert.h>
#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"

static JavaVM* jvm = NULL;
static jobject jobj;


void *callback_pthread(void* arg);

typedef struct
{
	JNIEnv *env;
	jobject obj;
    jclass clazz;
    jmethodID mid;
}add_node;

static jint native_nadd(JNIEnv *env, jobject obj, jint a, jint b)
{
	jint result = a + b;
	pthread_t thread;
	add_node *node = (add_node *)malloc(sizeof(add_node));
	node->env = env;
	node->obj = env->NewGlobalRef(obj);

    ALOGD("clazz is NUL000000000000000000000000AA\n");
    node->clazz = env->FindClass("com/neusoft/ivijni/Jniadd");
    if(node->clazz == NULL)
    {
        ALOGD("clazz is NULL 01AA \n");
        return 0;
    }

    ALOGD("clazz is NUL000000000000000000000001AA\n");

    node->mid = env->GetMethodID(node->clazz,"postEventFromNative","(I)V");
    if(node->mid == NULL)
    {
        ALOGD("mid is NULL\n");
        return 0;
    }
    ALOGD("clazz is NUL000000000000000000000002AA\n");
	pthread_create(&thread,NULL,callback_pthread,(void *)node);

	return result;
}	
void *callback_pthread(void* arg)
{
    ALOGD("clazz is NULL111111111111111100A\n");
	add_node *node = (add_node*)arg;
	JNIEnv *env = node->env;
	jobject obj = node->obj;
    jmethodID mid = node->mid;
	jvm->AttachCurrentThread(&env,NULL);


    ALOGD("clazz is NULL11111111111111111\n");
    /*jclass clazz;
    clazz = env->FindClass("com/neusoft/ivijni/Jniadd");

	if(clazz == NULL)
	{
		ALOGD("clazz is NULL\n");
		return 0;
    }*/
	


	ALOGD("clazz is NULL222222222222222222222\n");
	jint i = 0;
	while(1)
	{
		sleep(1);
		ALOGD("clazz is NULL333333333333333333\n");
		i++;
		env->CallVoidMethod(obj,mid,i);

	}
	return NULL;
}
static JNINativeMethod gMethods[] = {
	{"nadd", "(II)I", (void *)native_nadd},
};
static int register_android_jnitest_Nadd(JNIEnv *env)
{

    return android::AndroidRuntime::registerNativeMethods(env, "com/neusoft/ivijni/Jniadd", gMethods, NELEM(gMethods));
}
jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	JNIEnv *env = NULL;
	ALOGD("1111111111111111111111111111111111111111\n");
	jvm = vm;
	if (vm->GetEnv((void **)&env, JNI_VERSION_1_4) != JNI_OK) {
		ALOGD("Error GetEnv\n");
		return -1;
	}
    ALOGD("2222222222222222222222222222222222222\n");
	assert(env != NULL);
    ALOGD("33333333333333333333333333333333333\n");
	if (register_android_jnitest_Nadd(env) < 0) {
            ALOGD("444444444444444444444444444444444444\n");
		ALOGD("register_android_test_hello error.\n");
		return -1;
	}
        ALOGD("555555555555555555555555555555\n");
	return JNI_VERSION_1_4;
}
