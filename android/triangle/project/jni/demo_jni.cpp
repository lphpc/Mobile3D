

#include <stdio.h>
#include <jni.h>
#include <sys/time.h>
#include <time.h>
#include <android/log.h>
#include <stdint.h>
#include "app.h"

#ifdef __cplusplus
extern "C" {
#endif



static int  sWindowWidth  = 0;
static int  sWindowHeight = 0;
static int  sDemoStopped  = 0;
static long sTimeOffset   = 0;
static int  sTimeOffsetInit = 0;
static long sTimeStopped  = 0;

static long frames = 0;
static long interval = 0;
static long startTime = 0;

static char strFps[16]; 


static long
_getTime(void)
{
    struct timeval  now;

    gettimeofday(&now, NULL);
    return (long)(now.tv_sec*1000 + now.tv_usec/1000);
}

/* Call to initialize the graphics state */
void
Java_com_example_Triangle_Jade_nativeInit( JNIEnv*  env,  jobject  thiz, jint w, jint h  )
{

    __android_log_print(ANDROID_LOG_INFO, "Triangle", "This is nativeInit. before appInit");

    struct timeval timeNow;

    sWindowWidth = w;
    sWindowHeight = h;
    appInit(sWindowWidth, sWindowHeight);
    sDemoStopped = 0;
    sTimeOffsetInit = 0;

    __android_log_print(ANDROID_LOG_INFO, "Triangle", "This is nativeInit. after appInit");

    startTime = _getTime ();
    sprintf(strFps, "Fps:%.2f", 0.0f);
}

void
Java_com_example_Triangle_Jade_nativeResize( JNIEnv*  env, jobject  thiz, jint w, jint h )
{
    sWindowWidth  = w;
    sWindowHeight = h;
    __android_log_print(ANDROID_LOG_INFO, "Triangle", "resize w=%d h=%d", w, h);
}

/* Call to finalize the graphics state */
void
Java_com_example_Triangle_Jade_nativeDone( JNIEnv*  env )
{
    appDeinit();
    __android_log_print(ANDROID_LOG_INFO, "Triangle", "nativeDone");
}

/* This is called to indicate to the render loop that it should
 * stop as soon as possible.
 */
void
Java_com_example_Triangle_Jade_nativePause( JNIEnv*  env )
{
    sDemoStopped = !sDemoStopped;
    if (sDemoStopped) {
        /* we paused the animation, so store the current
         * time in sTimeStopped for future nativeRender calls */
        sTimeStopped = _getTime();
    } else {
        /* we resumed the animation, so adjust the time offset
         * to take care of the pause interval. */
        sTimeOffset -= _getTime() - sTimeStopped;
    }

    __android_log_print(ANDROID_LOG_INFO, "Triangle", "nativePause occur.");
}

/* Call to render the next GL frame */
void
Java_com_example_Triangle_Jade_nativeRender( JNIEnv*  env )
{
    struct timeval timeNow;

    long   curTime;

    /* NOTE: if sDemoStopped is TRUE, then we re-render the same frame
     *       on each iteration.
     */
    if (sDemoStopped) {
        curTime = sTimeStopped + sTimeOffset;
    } else {
        curTime = _getTime() + sTimeOffset;
        if (sTimeOffsetInit == 0) {
            sTimeOffsetInit = 1;
            sTimeOffset     = -curTime;
            curTime         = 0;
        }
    }

    //__android_log_print(ANDROID_LOG_INFO, "Triangle", "curTime=%ld", curTime);
    appRender(curTime, sWindowWidth, sWindowHeight);

    frames++;

    interval = _getTime () - startTime;

    //__android_log_print(ANDROID_LOG_INFO, "Triangle", "Fps\t\t:%.2f", frames * 1000.0f / interval);

    sprintf(strFps, "Fps:%.2f.\n", frames * 1000.0f / interval);

    //__android_log_print(ANDROID_LOG_INFO, "Triangle", "strFps: %s.\n", strFps);
    
}


void
Java_com_example_Triangle_Jade_nativeSetRotate ( JNIEnv*  env, jobject  thiz, jfloat x, jfloat y, jfloat z)
{
    float fx, fy, fz;
    int t;

    fx = x;
    fy = y;
    fz = z;

    __android_log_print(ANDROID_LOG_INFO, "Triangle", "this is nativeglRotatef.\n");
    __android_log_print(ANDROID_LOG_INFO, "Triangle", "jx=%f, jy=%f, jz=%d\n", x, y, z);
    __android_log_print(ANDROID_LOG_INFO, "Triangle", "fx=%f, fy=%f, fz=%f\n", fx, fy, fz);
    //__android_log_print(ANDROID_LOG_INFO, "Triangle", "glx=%f, gly=%f, glz=%d\n", (GLfloat)fx, (GLfloat)fy, (GLfloat)fz);

    //setRotate ((GLfloat)fx, (GLfloat)fy, (GLfloat)fz);
    //setRotate (10.0f, 10.0f, 10.0f);



///    setModelRotate ((int)fx, (int)fy, (int)fz);
       appSetModelRotate (fx, fy, fz);





/*
    test_float (10.0);
    test_int (5);
    test_outside_float ();
    test_int_float (50);
    test_outside_float ();
*/
}


void
Java_com_example_Triangle_Jade_nativeSetTextureOffset ( JNIEnv*  env, jobject  thiz, jfloat x, jfloat y, jfloat z)
{
    float fx, fy, fz;

    fx = x;
    fy = y;
    fz = z;

    __android_log_print(ANDROID_LOG_INFO, "Triangle", "this is nativesetTextureOffset.\n");
    __android_log_print(ANDROID_LOG_INFO, "Triangle", "jx=%f, jy=%f, jz=%d\n", x, y, z);
    __android_log_print(ANDROID_LOG_INFO, "Triangle", "fx=%f, fy=%f, fz=%f\n", fx, fy, fz);

///    setModelTextureOffset ((double)fx, (double)fy, (double)fz);
    appSetModelTextureOffset (fx, fy, fz);
    //setTextureOffset ((GLfloat)fx, (GLfloat)fy, (GLfloat)fz);

    //test_outside_float ();
}

void
Java_com_example_Triangle_Jade_nativeSetScale ( JNIEnv*  env, jobject  thiz, jfloat x, jfloat y, jfloat z)
{
    float fx, fy, fz;
    int t;

    fx = x;
    fy = y;
    fz = z;

    appSetModelScale (fx, fy, fz);


}

void
Java_com_example_Triangle_Jade_nativeSetPosition ( JNIEnv*  env, jobject  thiz, jfloat x, jfloat y, jfloat z)
{
    float fx, fy, fz;
    int t;

    fx = x;
    fy = y;
    fz = z;

    appSetModelPosition (fx, fy, fz);


}

#ifdef __cplusplus
}
#endif

