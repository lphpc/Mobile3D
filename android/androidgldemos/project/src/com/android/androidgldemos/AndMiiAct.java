
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

public class AndMiiAct extends Activity {

    private static final String TAG = "AndMiiAct";
    private float texureOffset = 0.0f;

	private static final int eyebrowNum = 3;
	private static final int eyeNum = 3;
	private static final int noseNum = 3;
	private static final int mouthNum = 3;
	private int eyebrowId = 0;
	private int eyeId = 0;
	private int noseId = 0;
	private int mouthId = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mGLView = new DemoGLSurfaceViewAndMii(this);
        setContentView(mGLView);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Jade.nativeDone(Constants.LIGHTMATERIALID);
    }



    //@Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {

        switch (keyCode) {

            case KeyEvent.KEYCODE_BACK:
                break;

            case KeyEvent.KEYCODE_DPAD_LEFT:
                Log.d (TAG, "Key LEFT is pressed.\n");
            	if (eyebrowId < eyebrowNum - 1)
                	eyebrowId++;
            	else
                	eyebrowId = 0;


                Jade.nativeSetMiiEyebrow (eyebrowId);
                break;

            case KeyEvent.KEYCODE_DPAD_RIGHT:
                Log.d (TAG, "Key RIGTH is pressed.\n");
                //nativeglRotatef (0, 0, 0);
            	if (eyeId < eyeNum - 1)
                	eyeId++;
            	else
                	eyeId = 0;

                Jade.nativeSetMiiEye (eyeId);
                break;

            case KeyEvent.KEYCODE_DPAD_UP:
            	if (noseId < noseNum - 1)
                	noseId++;
            	else
                	noseId = 0;

                Jade.nativeSetMiiNose (noseId);

                break;

            case KeyEvent.KEYCODE_DPAD_DOWN:
            	if (mouthId < mouthNum - 1)
                	mouthId++;
            	else
                	mouthId = 0;

                Jade.nativeSetMiiMouth (mouthId);
                break;

            case KeyEvent.KEYCODE_DPAD_CENTER:

                if (texureOffset > -0.75f)
                    texureOffset -= 0.25f;
                else
                    texureOffset = 0.0f;

                Jade.nativeSetTextureOffset (0.0f, texureOffset, 0.0f, Constants.LIGHTMATERIALID );

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

class DemoGLSurfaceViewAndMii extends GLSurfaceView {

    private int downX = 0;
    private int downY = 0;


    public DemoGLSurfaceViewAndMii(Context context) {
        super(context);
        mRenderer = new DemoRendererAndMii();
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


            Jade.nativeSetRotate (0.0f, angleY, 0.0f, Constants.LIGHTMATERIALID);
            //Jade.nativeSetRotate (angleX, angleY, 0.0f);

            downX = x;
            downY = y;

       }
       else if (eventAction == MotionEvent.ACTION_UP) {

            downX = 0;
            downY = 0;

       }

        return true;

    }

    DemoRendererAndMii mRenderer;
    float angleY = 0.0f;
    float angleX = 0.0f;

}

class DemoRendererAndMii implements GLSurfaceView.Renderer {
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        Jade.nativeInit(320, 480, Constants.LIGHTMATERIALID);
        Jade.nativeSetScale (1.0f, 1.0f, 1.0f, Constants.LIGHTMATERIALID);
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {
        //gl.glViewport(0, 0, w, h);
        Jade.nativeResize(w, h);
    }

    public void onDrawFrame(GL10 gl) {
        Jade.nativeRender(Constants.LIGHTMATERIALID);
    }

}
