
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLES/gl.h> /* For NDK*/
#include <assert.h>
#include <android/log.h>

#include "app.h"
#include "flotte.h"


#ifdef __cplusplus
extern "C" {
#endif


static long sStartTick = 0;
static long sTick = 0;

static int  action_idx = 0;

static M3D::World *world;
static M3D::Camera *camera = NULL;

static dmFlotte *gFlotte = NULL;
static float  pX = 0.0f;
static float  pY = 0.0f;
static int    waveFlag = 0;


///////////////////////////////////////////////////////////////////////////////

// Called from the app framework.
void appInitWater(int width, int height)
{
	world = new M3D::World ();
	world->setSize (320, 430);
	world->init ();

    camera = new M3D::Camera ();
    camera->setEye (0.0f, 0.0f, 5.0f);

    world->setCamera (camera);


	gFlotte = new dmFlotte(FLOT_LOWRES);

}


// Called from the app framework.
void appDeinitWater()
{

    FREEANDNULL (gFlotte);
    FREEANDNULL (camera);
    FREEANDNULL (world);
	
}

// Called from the app framework.
/* The tick is current time in milliseconds, width and height
 * are the image dimensions to be rendered.
 */
void appRenderWater(long tick, int width, int height)
{
    if (sStartTick == 0)
        sStartTick = tick;

    // Actual tick value is "blurred" a little bit.
    sTick = (sTick + tick - sStartTick) >> 1;

    world->prepareRender ();

	//Get wave by click screen
	if (waveFlag){
		gFlotte->setWave(-pX,-pY,  128);
	}
/*
	//auto play wave
    gFlotte->runWave(0.0f, 2.0f, 4.0f, 32); 
    gFlotte->runWave(400.0f, 5.0f, 3.0f, 32);
    gFlotte->runWave(800.0f, 3.0f, 2.0f, 32);
    gFlotte->runWave(1000.0f, 4.0f, 3.0f, 32); */

    gFlotte->update();

    gFlotte->build();

	
    gFlotte->display();

	world->finishRender ();

}

void appSetModelTextureOffsetWater (float x, float y, float z) {


    //LOGD ("appSetModelFlagOffset: x=%f, y=%f, z=%f\n", x, y, z);


}


void appSetModelRotateWater (float x, float y, float z) {


}

void appSetModelScaleWater (float x, float y, float z) {


}

void appSetModelPositionWater (float x, float y, float z) {


}
/*
void fontRender (int x, int y, const char *string) {

}
*/

void appSetWaterWave (int x, int y, int width, int height) {

	pX =-float(x)/width; //(float( x) - vsizeX/2.0f)/vsizeX ;
    pY = float(y)/height; //(float( y) - vsizeY/2.0f)/vsizeY;

    waveFlag = 1;

}

void appClearWaterWave () {

	waveFlag = 0;
}



#ifdef __cplusplus
}
#endif

