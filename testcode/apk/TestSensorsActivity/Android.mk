LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_DEX_PREOPT := false

LOCAL_MODULE_TAGS := optional
LOCAL_PROGUARD_ENABLED := disabled

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_PACKAGE_NAME := TestSensorsActivity
LOCAL_CERTIFICATE := platform
LOCAL_SDK_VERSION := current

LOCAL_RESOURCE_DIR += $(LOCAL_PATH)/res



include $(BUILD_PACKAGE)

# Use the folloing include to make our test app
include $(call all-makefiles-under,$(LOCAL_PATH))

