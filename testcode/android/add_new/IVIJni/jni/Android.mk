#
# Copyright 2014, Neusoftware 
#
#  iPod
#

JNI_LOCAL_PATH:= $(call my-dir)

include $(call all-subdir-makefiles)

# Build the iPod player library
# ============================================================
LOCAL_PATH:= $(JNI_LOCAL_PATH)
include $(CLEAR_VARS)

LOCAL_SRC_FILES :=  \
	android_jnitest_Nadd.cpp

LOCAL_MODULE := libivi_jni
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := libcutils libandroid_runtime libstlport libc liblog

include $(BUILD_SHARED_LIBRARY)

# Build the iPod metadata library
# ============================================================
