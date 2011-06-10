
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLES/gl.h> /* For NDK*/
#include <assert.h>
#include <android/log.h>

#include "app.h"
#include "data_triangle.h"


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
static M3D::Model *model = NULL;


///////////////////////////////////////////////////////////////////////////////

// Called from the app framework.
void appInitTriangle(int width, int height)
{
	world = new M3D::World ();
	world->setSize (320, 430);
	world->init ();

    camera = new M3D::Camera ();
    camera->setEye (0.0f, 0.0f, 5.0f);

    world->setCamera (camera);

    model = new M3D::Model ();
    model->setMeshCount (MESH_NUM_TRIANGLE);

    //init first triangle
    model->setVertices(vertices0, VERTEX_NUM_TRIANGLE * 3 * sizeof(GLfloat), 0);
    model->setColors(colors, VERTEX_NUM_TRIANGLE * 4 * sizeof(GLubyte), 0);
    model->setTriangleNums(1, 0);

}


// Called from the app framework.
void appDeinitTriangle()
{
	FREEANDNULL (model);
	FREEANDNULL (camera);
	FREEANDNULL (world);
}

// Called from the app framework.
/* The tick is current time in milliseconds, width and height
 * are the image dimensions to be rendered.
 */
void appRenderTriangle(long tick, int width, int height)
{
    if (sStartTick == 0)
        sStartTick = tick;

    // Actual tick value is "blurred" a little bit.
    sTick = (sTick + tick - sStartTick) >> 1;

	world->prepareRender ();
	model->renderModel ();
	world->finishRender ();


}

void appSetModelTextureOffsetTriangle (float x, float y, float z) {


    //LOGD ("appSetModelTextureOffset: x=%f, y=%f, z=%f\n", x, y, z);


}


void appSetModelRotateTriangle (float x, float y, float z) {


}

void appSetModelScaleTriangle (float x, float y, float z) {


}

void appSetModelPositionTriangle (float x, float y, float z) {


}
/*
void fontRender (int x, int y, const char *string) {

}
*/

#ifdef __cplusplus
}
#endif

