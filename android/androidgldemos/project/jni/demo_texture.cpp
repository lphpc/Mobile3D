
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLES/gl.h> /* For NDK*/
#include <assert.h>
#include <android/log.h>

#include "app.h"
#include "data_texture.h"

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
static M3D::ImageBMP *image = NULL;


///////////////////////////////////////////////////////////////////////////////

// Called from the app framework.
void appInitTexture(int width, int height)
{
	world = new M3D::World ();
	world->setSize (320, 430);
	world->init ();

    camera = new M3D::Camera ();
    camera->setEye (0.0f, 0.0f, 5.0f);

    world->setCamera (camera);

    image = new M3D::ImageBMP ();
    Texture *texture = image->loadTexture ("/data/mobile3d/androidgldemos/texture/rocks.bmp");

    model = new M3D::Model ();
    model->setMeshCount (MESH_NUM);

    model->setVertices(afVerticesTexture, VERTEX_NUM_TEXTURE * 3 * sizeof(GLfloat), 0);
    model->setIndices(afVertIndicesTexture, TRIANGLE_NUM_TEXTURE * 3 * sizeof(GLshort), 0);
    model->setUvs(afTexCoordTexture, VERTEX_NUM_TEXTURE * 2 * sizeof (GLfloat), 0);
    model->setTriangleNums(TRIANGLE_NUM_TEXTURE, 0);
    if (texture != NULL)
        model->setTextureId (texture->textureId, 0);

	FREEANDNULL (texture);

}


// Called from the app framework.
void appDeinitTexture()
{
    FREEANDNULL (image);
    FREEANDNULL (model);
    FREEANDNULL (camera);
    FREEANDNULL (world);
}

// Called from the app framework.
/* The tick is current time in milliseconds, width and height
 * are the image dimensions to be rendered.
 */
void appRenderTexture(long tick, int width, int height)
{
    if (sStartTick == 0)
        sStartTick = tick;

    // Actual tick value is "blurred" a little bit.
    sTick = (sTick + tick - sStartTick) >> 1;

	world->prepareRender ();
	model->renderModel ();
	world->finishRender ();


}

void appSetModelTextureOffsetTexture (float x, float y, float z) {


    //LOGD ("appSetModelTextureOffset: x=%f, y=%f, z=%f\n", x, y, z);


}


void appSetModelRotateTexture (float x, float y, float z) {


}

void appSetModelScaleTexture (float x, float y, float z) {


}

void appSetModelPositionTexture (float x, float y, float z) {


}
/*
void fontRender (int x, int y, const char *string) {

}
*/

#ifdef __cplusplus
}
#endif

