LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	local_time.cpp

LOCAL_SHARED_LIBRARIES := \
	libcutils libhardware libc

LOCAL_MODULE:= test-local_time

LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)


