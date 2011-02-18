LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := photo3d

LOCAL_CFLAGS := -DANDROID_NDK \
                -DDISABLE_IMPORTGL 

LOCAL_SRC_FILES := \
    demo.cpp \
    demo_jni.cpp \

LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog -lmobile3d

include $(BUILD_SHARED_LIBRARY)
