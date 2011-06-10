
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLES/gl.h> /* For NDK*/
#include <assert.h>
#include <android/log.h>

#include "app.h"
#include "data_caustics.h"

#define MESH_NUM 1
#define NUM_PATTERNS 32

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

static Texture *texture_bottom = NULL;
//static Texture *texture_top = NULL;
static Texture **texture_caust = NULL;

static int currentCaustic = 0;
static int causticIncrement = 2;



///////////////////////////////////////////////////////////////////////////////

// Called from the app framework.
void appInitCaustics(int width, int height)
{
	world = new M3D::World ();
	world->setSize (320, 430);
	world->init ();

    camera = new M3D::Camera ();
    camera->setEye (0.0f, 0.0f, 5.0f);

    world->setCamera (camera);

    image = new M3D::ImageBMP ();
    //texture_top = image->loadTexture ("/data/mobile3d/caustics/caust.bmp");
    texture_bottom = image->loadTexture ("/data/mobile3d/androidgldemos/caustics/rocks.bmp");

	/*Load caustics texture*/

	texture_caust = (Texture**)malloc (NUM_PATTERNS * sizeof (Texture*));
	memset (texture_caust, 0, NUM_PATTERNS * sizeof (Texture*));

	for (int i = 0; i < NUM_PATTERNS; i += causticIncrement){
		char filename [80];

		sprintf(filename, "/data/mobile3d/androidgldemos/caustics/caust%02d.bmp", i);
		texture_caust[i] = image->loadTexture (filename);
		
	}



    model = new M3D::Model ();
    model->setMeshCount (MESH_NUM);

    model->setVertices(afVerticesCaustics, VERTEX_NUM_CAUSTICS * 3 * sizeof(GLfloat), 0);
    model->setIndices(afVertIndicesCaustics, TRIANGLE_NUM_CAUSTICS * 3 * sizeof(GLshort), 0);
    model->setUvs(afTexCoordCaustics, VERTEX_NUM_CAUSTICS * 2 * sizeof (GLfloat), 0);
    model->setTriangleNums(TRIANGLE_NUM_CAUSTICS, 0);
/*
	if (texture != NULL)
        model->setTextureId (texture->textureId, 0);
*/
}


// Called from the app framework.
void appDeinitCaustics()
{

	free (texture_caust);
	//free (texture_top);
	free (texture_bottom);
    FREEANDNULL (image);
    FREEANDNULL (model);
    FREEANDNULL (camera);
    FREEANDNULL (world);

}

// Called from the app framework.
/* The tick is current time in milliseconds, width and height
 * are the image dimensions to be rendered.
 */
void appRenderCaustics(long tick, int width, int height)
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


    if (texture_caust[currentCaustic] != NULL) {
        model->setTextureId (texture_caust[currentCaustic]->textureId, 0);
        model->enableBlend (true, 0);
        //model->setBlendFunc (GL_ONE, GL_ZERO, 0);
        model->setBlendFunc (GL_ZERO, GL_SRC_COLOR, 0);
        model->renderModel ();
    }


	world->finishRender ();

	currentCaustic = (currentCaustic + causticIncrement) % NUM_PATTERNS;


}

void appSetModelTextureOffsetCaustics (float x, float y, float z) {


    //LOGD ("appSetModelTextureOffset: x=%f, y=%f, z=%f\n", x, y, z);


}


void appSetModelRotateCaustics (float x, float y, float z) {


}

void appSetModelScaleCaustics (float x, float y, float z) {


}

void appSetModelPositionCaustics (float x, float y, float z) {


}
/*
void fontRender (int x, int y, const char *string) {

}
*/

#ifdef __cplusplus
}
#endif

