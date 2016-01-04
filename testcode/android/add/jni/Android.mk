LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_SRC_FILES := \
	com_hello_jnitest.cpp
LOCAL_SHARED_LIBRARIES := \
	libandroid_runtime libcutils
LOCAL_MODULE := libhello_jni
include $(BUILD_SHARED_LIBRARY)
