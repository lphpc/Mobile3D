LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := triangle

LOCAL_CFLAGS := -DANDROID_NDK \
                -DDISABLE_IMPORTGL 

LOCAL_SRC_FILES := \
    demo.cpp \
    demo_jni.cpp \
	male_eyebrow_01_l

LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog -lmobile3d

include $(BUILD_SHARED_LIBRARY)
