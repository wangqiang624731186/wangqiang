LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	testhard.cpp

LOCAL_SHARED_LIBRARIES := \
	libcutils libhardware libc

LOCAL_MODULE:= test-hard

LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)


