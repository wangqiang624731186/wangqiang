LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	spi_test.c

LOCAL_SHARED_LIBRARIES := \
	libcutils libhardware libc

LOCAL_MODULE:= spi_test

LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)




