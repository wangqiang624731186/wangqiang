# File: Example
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
	startapk.c
LOCAL_SHARED_LIBRARIES := \
	libc  
LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := startapk

include $(BUILD_EXECUTABLE)

