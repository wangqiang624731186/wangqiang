# File: Example
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
	2.c
LOCAL_SHARED_LIBRARIES := \
	libc  
LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := cpu_test

include $(BUILD_EXECUTABLE)

