LOCAL_PATH:= $(call my-dir)

# the library
# ============================================================
include $(CLEAR_VARS)

LOCAL_PROGUARD_ENABLED := disabled

LOCAL_SRC_FILES := \
            $(call all-subdir-java-files) \	    
LOCAL_MODULE:= IVIJni
LOCAL_JAVA_LIBRARIES := core framework

include $(BUILD_STATIC_JAVA_LIBRARY)

#include $(BUILD_DROIDDOC)

include $(call all-makefiles-under, $(LOCAL_PATH))

#include $(BUILD_DROIDDOC)
