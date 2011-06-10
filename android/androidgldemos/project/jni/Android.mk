LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := androidgldemos

LOCAL_CFLAGS := -DANDROID_NDK \
                -DDISABLE_IMPORTGL 

LOCAL_SRC_FILES := \
    demo_triangle.cpp \
    demo_texture.cpp \
    demo_blending.cpp \
    demo_caustics.cpp \
    demo_flag.cpp \
    demo_water.cpp \
    flotte.cpp \
    demo_andmii.cpp \
    jni.cpp \
	data_triangle.h \
	data_texture.h \
	data_blending.h \
	data_caustics.h \
	data_flag.h \
    flotte.h \

LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog -lmobile3d

include $(BUILD_SHARED_LIBRARY)
