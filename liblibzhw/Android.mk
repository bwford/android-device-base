
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_SHARED_LIBRARIES := liblog libcutils libhardware
LOCAL_SRC_FILES := libzhw.c
LOCAL_MODULE := libzhw.omap4
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)