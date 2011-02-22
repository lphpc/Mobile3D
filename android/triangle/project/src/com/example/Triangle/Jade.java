
package com.example.Triangle;

public class Jade {

    public static native void nativeSetTextureOffset (float x, float y, float z);
    public static native void nativeDone();
    public static native void nativePause();
    public static native void nativeSetRotate (float x, float y, float z);
    public static native void nativeInit(int w, int h);
    public static native void nativeResize(int w, int h);
    public static native void nativeRender();
    public static native void nativeSetScale (float x, float y, float z);

	static {
		System.loadLibrary("triangle");
	}
}

