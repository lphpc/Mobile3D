
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLES/gl.h> /* For NDK*/
#include <assert.h>
#include <android/log.h>

#include "app.h"
//#include "data.h"
//#include "data_triangle.h"


// Total run length is 20 * camera track base unit length (see cams.h).
#define RUN_LENGTH  (20 * CAMTRACK_LEN)


using namespace M3D;

#ifdef __cplusplus
extern "C" {
#endif


static long sStartTick = 0;
static long sTick = 0;

static int  action_idx = 0;

M3D::World *world;
M3D::Camera *camera = NULL;
M3D::Light *light = NULL;
static GLfloat pos[4] = {0.0f, 10.0f, 20.0f, 1.0f};


ModelAM*      model_body;
ModelAM*      model_head;
ModelAM*      model_hair;
ModelAM*      model_eyebrow_l;
ModelAM*      model_eyebrow_r;
ModelAM*      model_eye_l;
ModelAM*      model_eye_r;
ModelAM*      model_nose;
ModelAM*      model_mouth;


///////////////////////////////////////////////////////////////////////////////



// Called from the app framework.
void appInit(int width, int height)
{
	world = new World ();
	world->setBgColor (0.0, 255.0, 0.0, 0.0);
	world->setSize (320, 430);
	world->init ();

    camera = new M3D::Camera ();
    camera->setEye (0.0f, 3.0f, 60.0f);

    world->setCamera (camera);

    light = new Light();
    light->setPosition(pos);
    world->setLight(light);

	model_body = new ModelAM ();
	model_body->loadModel ("/data/mobile3d/andmii/male_body_1.am");
	

    model_head = new ModelAM ();
	model_head->loadModel ("/data/mobile3d/andmii/male_head_changfang.am");


    model_hair = new ModelAM ();
	model_hair->loadModel ("/data/mobile3d/andmii/male_hair_01.am");


    model_eyebrow_l = new ModelAM ();
	model_eyebrow_l->loadModel ("/data/mobile3d/andmii/male_eyebrow_01_l.am");

    model_eyebrow_r = new ModelAM ();
	model_eyebrow_r->loadModel ("/data/mobile3d/andmii/male_eyebrow_01_r.am");


    model_eye_l = new ModelAM ();
	model_eye_l->loadModel ("/data/mobile3d/andmii/male_eye_02_l.am");

    model_eye_r = new ModelAM ();
	model_eye_r->loadModel ("/data/mobile3d/andmii/male_eye_02_r.am");

    model_nose = new ModelAM ();
	model_nose->loadModel ("/data/mobile3d/andmii/male_nose_01.am");

    model_mouth = new ModelAM ();
	model_mouth->loadModel ("/data/mobile3d/andmii/male_mouth_01.am");




}


// Called from the app framework.
void appDeinit()
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
void appRender(long tick, int width, int height)
{
    if (sStartTick == 0)
        sStartTick = tick;

    // Actual tick value is "blurred" a little bit.
    sTick = (sTick + tick - sStartTick) >> 1;

	world->prepareRender ();

    model_body->renderModel();
    model_head->renderModel();
    model_hair->renderModel();
    model_eyebrow_l->renderModel();
    model_eyebrow_r->renderModel();
    model_eye_l->renderModel();
    model_eye_r->renderModel();
    model_nose->renderModel();
    model_mouth->renderModel();

	world->finishRender ();


}

void appSetModelTextureOffset (float x, float y, float z) {


    //LOGD ("appSetModelTextureOffset: x=%f, y=%f, z=%f\n", x, y, z);


}


void appSetModelRotate (float x, float y, float z) {

	__android_log_print(ANDROID_LOG_INFO, "AndMii", "this is appSetModelRotate.\n");

}

void appSetModelScale (float x, float y, float z) {

	


}

void appSetModelPosition (float x, float y, float z) {


}
/*
void fontRender (int x, int y, const char *string) {

}
*/


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

