
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLES/gl.h> /* For NDK*/
#include <assert.h>
#include <android/log.h>

#include "app.h"


// Total run length is 20 * camera track base unit length (see cams.h).
#define RUN_LENGTH  (20 * CAMTRACK_LEN)


#ifdef __cplusplus
extern "C" {
#endif


static long sStartTick = 0;
static long sTick = 0;

static int  action_idx = 0;

static M3D::World *world;
static M3D::Camera *camera = NULL;
static M3D::Light *light = NULL;
//static GLfloat pos[4] = {1.0f, 1.0f, 1.0f, 0.0f};
//static GLfloat pos[4] = {0.0f, 10.0f, 15.0f, 1.0f};
static GLfloat pos[4] = {0.0f, 10.0f, 20.0f, 1.0f};

int body_id = 0;

int head_id = 0;

int hair_id = 0;

int eyebrow_l_id = 0;

int eyebrow_r_id = 0;

int eye_l_id = 0;

int eye_r_id = 0;

int nose_id = 0;

int mouth_id = 0;


static M3D::ModelAM *model_body = NULL;
static M3D::ModelAM *model_head = NULL;
static M3D::ModelAM *model_hair = NULL;
static M3D::ModelAM *model_eyebrow_l = NULL;
static M3D::ModelAM *model_eyebrow_r = NULL;
static M3D::ModelAM *model_eye_l = NULL;
static M3D::ModelAM *model_eye_r = NULL;
static M3D::ModelAM *model_nose = NULL;
static M3D::ModelAM *model_mouth = NULL;

extern bool loadAllMeshes ();
extern void destroyAllMeshes ();
extern void dumpBodies ();

///////////////////////////////////////////////////////////////////////////////



void createDefaultMii ()
{


    return;
}

void updateMiiEyebrow ()
{
}

void updateMiiEye ()
{
}


void updateMiiNose ()
{
}


void updateMiiMouth ()
{
}



// Called from the app framework.
void appInitAndMii(int width, int height)
{
	world = new M3D::World ();
	world->setBgColor (0.0, 255.0, 0.0, 0.0);
	world->setSize (320, 430);
	world->init ();

    camera = new M3D::Camera ();
    camera->setEye (0.0f, 3.0f, 60.0f);

    world->setCamera (camera);

    light = new M3D::Light();
    light->setPosition(pos);
    world->setLight(light);



}


// Called from the app framework.
void appDeinitAndMii()
{
    delete world;
    delete camera;
    delete light;

    delete model_body;
    delete model_head;
    delete model_hair;
    delete model_eyebrow_l;
    delete model_eyebrow_r;
    delete model_eye_l;
    delete model_eye_r;
    delete model_nose;
    delete model_mouth;



}

// Called from the app framework.
/* The tick is current time in milliseconds, width and height
 * are the image dimensions to be rendered.
 */
void appRenderAndMii(long tick, int width, int height)
{
    if (sStartTick == 0)
        sStartTick = tick;

    // Actual tick value is "blurred" a little bit.
    sTick = (sTick + tick - sStartTick) >> 1;



}

void appSetModelTextureOffsetAndMii (float x, float y, float z) {


    //LOGD ("appSetModelTextureOffset: x=%f, y=%f, z=%f\n", x, y, z);


}


void appSetModelRotateAndMii (float x, float y, float z) {

	__android_log_print(ANDROID_LOG_INFO, "AndMii", "this is appSetModelRotate.\n");


}

void appSetModelScaleAndMii (float x, float y, float z) {

	


}

void appSetModelPositionAndMii (float x, float y, float z) {


}
/*
void fontRender (int x, int y, const char *string) {

}
*/


void appSetMiiEyebrow (int id)
{
	eyebrow_l_id = id;
	eyebrow_r_id = id;
}

void appSetMiiEye (int id)
{
	eye_l_id = id;
	eye_r_id = id;
}

void appSetMiiNose (int id)
{
	nose_id = id;
	nose_id = id;
}

void appSetMiiMouth (int id)
{
	mouth_id = id;
	mouth_id = id;
}


#ifdef __cplusplus
}
#endif

