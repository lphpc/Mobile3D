
package com.android.androidgldemos;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.KeyEvent;
import android.util.Log;

public class TriangleAct extends Activity {

    private static final String TAG = "Triangle";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mGLView = new DemoGLSurfaceViewTriangle(this);
        setContentView(mGLView);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Jade.nativeDone(0);
        //android.os.Process.killProcess(android.os.Process.myPid());
    }



    //@Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {

        switch (keyCode) {

            case KeyEvent.KEYCODE_BACK:
                break;

            case KeyEvent.KEYCODE_DPAD_RIGHT:
                Log.d (TAG, "Key RIGTH is pressed.\n");
                //nativeglRotatef (0, 0, 0);
                break;

            case KeyEvent.KEYCODE_DPAD_LEFT:
                Log.d (TAG, "Key LEFT is pressed.\n");
                break;

            case KeyEvent.KEYCODE_DPAD_UP:
                break;

            case KeyEvent.KEYCODE_DPAD_DOWN:
                break;

            case KeyEvent.KEYCODE_DPAD_CENTER:
                break;

        }

        return super.onKeyDown(keyCode, event);
    }


    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    private GLSurfaceView mGLView;


}

class DemoGLSurfaceViewTriangle extends GLSurfaceView {

    private int downX = 0;
    private int downY = 0;


    public DemoGLSurfaceViewTriangle(Context context) {
        super(context);
        mRenderer = new DemoRendererTriangle();
        setRenderer(mRenderer);
    }

    public boolean onTouchEvent(final MotionEvent event) {


        int eventAction = event.getAction();

        int x = (int)event.getX();
        int y = (int)event.getY();



        if (eventAction == MotionEvent.ACTION_DOWN) {

            downX = x;
            downY = y;
        }

        else if (eventAction == MotionEvent.ACTION_MOVE) {

            if ((x - downX) != 0) {

                angleY = angleY + (x - downX) * 180 / getWidth ();
                angleY = angleY % 360;


                //Log.d ("AndMiiAct", "x = " + x + " downX = " + downX + "angleY = " + angleY);
            }

            if ((y - downY) != 0) {

                angleX = angleX + (y - downY) * 180 / getHeight ();
                angleX = angleX % 360;


                //Log.d ("AndMiiAct", "y = " + y + " downY = " + downY + "angleX = " + angleX);
            }


            Jade.nativeSetRotate (angleX, angleY, 0.0f, 0);

            downX = x;
            downY = y;

       }
       else if (eventAction == MotionEvent.ACTION_UP) {

            downX = 0;
            downY = 0;

       }

        return true;

    }

    DemoRendererTriangle mRenderer;
    float angleY = 0.0f;
    float angleX = 0.0f;

}

class DemoRendererTriangle implements GLSurfaceView.Renderer {
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        Jade.nativeInit(320, 480, 0);
        Jade.nativeSetScale (1.0f, 1.0f, 1.0f, 0);
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {
        //gl.glViewport(0, 0, w, h);
        Jade.nativeResize(w, h);
    }

    public void onDrawFrame(GL10 gl) {
        Jade.nativeRender(0);
    }

}
