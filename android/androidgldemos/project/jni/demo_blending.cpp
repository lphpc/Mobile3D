
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLES/gl.h> /* For NDK*/
#include <assert.h>
#include <android/log.h>

#include "app.h"
#include "data_blending.h"

#define MESH_NUM 1

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
static M3D::ImageRGB *image = NULL;

static Texture *texture_bottom = NULL;
static Texture *texture_top = NULL;



///////////////////////////////////////////////////////////////////////////////

// Called from the app framework.
void appInitBlending(int width, int height)
{
	world = new M3D::World ();
	world->setSize (320, 430);
	world->init ();

    camera = new M3D::Camera ();
    camera->setEye (0.0f, 0.0f, 5.0f);

    world->setCamera (camera);

    image = new M3D::ImageRGB ();
    //Texture *texture = image->loadTexture ("/data/mobile3d/texture/rocks.bmp");
    texture_top = image->loadRGBTexture ("/data/mobile3d/androidgldemos/blending/floor.rgb");
    texture_bottom = image->loadAlphaTexture ("/data/mobile3d/androidgldemos/blending/caust00.bw");



    model = new M3D::Model ();
    model->setMeshCount (MESH_NUM);

    model->setVertices(afVerticesBlending, VERTEX_NUM_BLENDING * 3 * sizeof(GLfloat), 0);
    model->setIndices(afVertIndicesBlending, TRIANGLE_NUM_BLENDING * 3 * sizeof(GLshort), 0);
    model->setUvs(afTexCoordBlending, VERTEX_NUM_BLENDING * 2 * sizeof (GLfloat), 0);
    model->setTriangleNums(TRIANGLE_NUM_BLENDING, 0);
/*
	if (texture != NULL)
        model->setTextureId (texture->textureId, 0);
*/
}


// Called from the app framework.
void appDeinitBlending()
{
    FREEANDNULL (texture_top);
    FREEANDNULL (texture_bottom);
    FREEANDNULL (image);
    FREEANDNULL (model);
    FREEANDNULL (camera);
    FREEANDNULL (world);

}

// Called from the app framework.
/* The tick is current time in milliseconds, width and height
 * are the image dimensions to be rendered.
 */
void appRenderBlending(long tick, int width, int height)
{
    if (sStartTick == 0)
        sStartTick = tick;

    // Actual tick value is "blurred" a little bit.
    sTick = (sTick + tick - sStartTick) >> 1;

	world->prepareRender ();
	//model->renderModel ();


    if (texture_bottom != NULL) {
		//model->setPosition (0.0, 0.0, 0.0);
        model->setTextureId (texture_bottom->textureId, 0);
        model->enableBlend (false, 0);
        model->renderModel ();
    }



    if (texture_top != NULL) {
		//model->setPosition (0.0, -10.0, 1.0);
		//model->setScale (-10.0, -10.0, -10.0);
        model->setTextureId (texture_top->textureId, 0);
        model->enableBlend (true, 0);
        //model->setBlendFunc (GL_ONE, GL_ZERO, 0);
        model->setBlendFunc (GL_ZERO, GL_SRC_COLOR, 0);
        model->renderModel ();
    }


	world->finishRender ();


}

void appSetModelTextureOffsetBlending (float x, float y, float z) {


    //LOGD ("appSetModelTextureOffset: x=%f, y=%f, z=%f\n", x, y, z);


}


void appSetModelRotateBlending (float x, float y, float z) {


}

void appSetModelScaleBlending (float x, float y, float z) {


}

void appSetModelPositionBlending (float x, float y, float z) {


}
/*
void fontRender (int x, int y, const char *string) {

}
*/

#ifdef __cplusplus
}
#endif

