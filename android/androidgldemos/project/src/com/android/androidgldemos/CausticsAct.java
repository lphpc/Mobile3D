
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

public class CausticsAct extends Activity {

    private static final String TAG = "Caustics";
    private float texureOffset = 0.0f;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mGLView = new DemoGLSurfaceViewCaustics(this);
        setContentView(mGLView);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Jade.nativeDone(Constants.CAUSTICSID);
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

                if (texureOffset > -0.75f)
                    texureOffset -= 0.25f;
                else
                    texureOffset = 0.0f;

                Jade.nativeSetTextureOffset (0.0f, texureOffset, 0.0f, Constants.CAUSTICSID );

                break;



        }

        return super.onKeyDown(keyCode, event);
    }


    @Override
    protected void onPause() {
        super.onPause();
        mGLView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        mGLView.onResume();
    }

    private GLSurfaceView mGLView;


}

class DemoGLSurfaceViewCaustics extends GLSurfaceView {

    private int downX = 0;
    private int downY = 0;


    public DemoGLSurfaceViewCaustics(Context context) {
        super(context);
        mRenderer = new DemoRendererCaustics();
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


            Jade.nativeSetRotate (angleX, angleY, 0.0f, Constants.CAUSTICSID);

            downX = x;
            downY = y;

       }
       else if (eventAction == MotionEvent.ACTION_UP) {

            downX = 0;
            downY = 0;

       }

        return true;

    }

    DemoRendererCaustics mRenderer;
    float angleY = 0.0f;
    float angleX = 0.0f;

}

class DemoRendererCaustics implements GLSurfaceView.Renderer {
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        Jade.nativeInit(320, 480, Constants.CAUSTICSID);
        Jade.nativeSetScale (1.0f, 1.0f, 1.0f, Constants.CAUSTICSID);
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {
        //gl.glViewport(0, 0, w, h);
        Jade.nativeResize(w, h);
    }

    public void onDrawFrame(GL10 gl) {
        Jade.nativeRender(Constants.CAUSTICSID);
    }

}
