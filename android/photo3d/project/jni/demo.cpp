
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLES/gl.h> /* For NDK*/
#include <assert.h>
#include <android/log.h>

#include "app.h"


// Total run length is 20 * camera track base unit length (see cams.h).
#define RUN_LENGTH  (20 * CAMTRACK_LEN)

#define GRID 1
#define GRID_COUNT 24

using namespace M3D;

#ifdef __cplusplus
extern "C" {
#endif


static long sStartTick = 0;
static long sTick = 0;

static int  action_idx = 0;

M3D::World *world;
M3D::Camera *camera = NULL;

#ifdef GRID
M3DQuad *quadGrid[GRID_COUNT];
#else
M3DQuad *quad = NULL;
#endif



///////////////////////////////////////////////////////////////////////////////


#ifdef GRID
void initGrid ()
{
	for (int i = 0; i < GRID_COUNT; i++){
		quadGrid[i] = new M3DQuad ();
		quadGrid[i]->create ((float)(i/4) - 1.5, (float)(i%4) - 0.8, 0.9, 0.9, 
				"/data/mobile3d/photo3d/android-logo-white.tga");
	}	
}

void drawGrid ()
{
	for (int i = 0; i < GRID_COUNT; i++){
		
		//quadGrid[i]->rotate (angle_x, angle_y, 0.0);
		quadGrid[i]->draw ();
	}
}

void rotateGrid (float x, float y, float z)
{
	for (int i = 0; i < GRID_COUNT; i++){
		
		quadGrid[i]->rotate (x, y, 0.0);
	}
}


void destroyGrid ()
{
	for (int i = 0; i < GRID_COUNT; i++){
		FREEANDNULL (quadGrid[i]);
	}

}

#endif


// Called from the app framework.
void appInit(int width, int height)
{
	world = new World ();
	world->setBgColor (0.0, 0.0, 0.0, 0.0);
	world->setSize (320, 430);
	world->init ();

    camera = new M3D::Camera ();
    camera->setEye (0.0f, 0.0f, 5.0f);

    world->setCamera (camera);

#ifdef GRID
	initGrid ();
#else
	quad = new M3DQuad ();
	quad->create (-1.0, 1.0, 2.0, 2.0, "/data/mobile3d/photo3d/android-logo-white.tga");
#endif




}


// Called from the app framework.
void appDeinit()
{
    delete world;
    delete camera;

#ifdef GRID
	destroyGrid ();
#else
	delete quad;
#endif

}

// Called from the app framework.
/* The tick is current time in milliseconds, width and height
 * are the image dimensions to be rendered.
 */
void appRender(long tick, int width, int height)
{
    if (sStartTick == 0)
        sStartTick = tick;

    // Actual tick value is "blurred" a little bit.
    sTick = (sTick + tick - sStartTick) >> 1;

	world->prepareRender ();
#ifdef GRID
	drawGrid ();
#else
	quad->draw ();
#endif

	world->finishRender ();


}

void appSetModelTextureOffset (float x, float y, float z) {


    //LOGD ("appSetModelTextureOffset: x=%f, y=%f, z=%f\n", x, y, z);


}


void appSetModelRotate (float x, float y, float z) {

	__android_log_print(ANDROID_LOG_INFO, "Photo3D", "this is appSetModelRotate.\n");

#ifdef GRID
	rotateGrid (x, y, z);
#else
	quad->rotate (x, y, z);
#endif
	

}

void appSetModelScale (float x, float y, float z) {

	


}

void appSetModelPosition (float x, float y, float z) {


}


void appSetMiiEyebrow (int id)
{
}

void appSetMiiEye (int id)
{
}

void appSetMiiNose (int id)
{
}

void appSetMiiMouth (int id)
{
}


#ifdef __cplusplus
}
#endif

