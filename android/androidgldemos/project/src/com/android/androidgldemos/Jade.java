
package com.android.androidgldemos;

public class Jade {

    public static native void nativeSetTextureOffset (float x, float y, float z, int demoId);
    public static native void nativeDone(int demoId);
    public static native void nativePause();
    public static native void nativeSetRotate (float x, float y, float z, int demoId);
    public static native void nativeInit(int w, int h, int demoId);
    public static native void nativeResize(int w, int h);
    public static native void nativeRender(int demoId);
    public static native void nativeSetScale (float x, float y, float z, int demoId);


    public static native void nativeSetMiiEyebrow (int id);
    public static native void nativeSetMiiEye (int id);
    public static native void nativeSetMiiNose (int id);
    public static native void nativeSetMiiMouth (int id);


    public static native void nativeSetWave (int x, int y);
    public static native void nativeClearWave ();

	static {
		System.loadLibrary("androidgldemos");
	}
}

