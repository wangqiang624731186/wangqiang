# File: Example
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
	gps_property.c
LOCAL_SHARED_LIBRARIES := \
	libc  libcutils
LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := gps_property

include $(BUILD_EXECUTABLE)

