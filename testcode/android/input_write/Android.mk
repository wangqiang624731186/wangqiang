# File: Example
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
	input_write.c
LOCAL_SHARED_LIBRARIES := \
	libc  
LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := input_write

include $(BUILD_EXECUTABLE)

