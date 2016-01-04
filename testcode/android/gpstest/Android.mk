LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	gps.cpp

LOCAL_SHARED_LIBRARIES := \
	libcutils libhardware libc

LOCAL_MODULE:= test-gps

LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	gps_ttymxc1.cpp

LOCAL_SHARED_LIBRARIES := \
	libcutils libhardware libc

LOCAL_MODULE:= test-gps-tty

LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)



include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	core_gps_daemon.c

LOCAL_SHARED_LIBRARIES := \
	libcutils libhardware libc

LOCAL_MODULE:= core_gps_daemon

LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)

