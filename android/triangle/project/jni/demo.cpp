
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLES/gl.h> /* For NDK*/
#include <assert.h>
#include <android/log.h>

#include "app.h"


//#define QUAD  1

#ifdef QUAD

#include "data.h"

#else

#include "male_eyebrow_01_l.h"

#endif


// Total run length is 20 * camera track base unit length (see cams.h).
#define RUN_LENGTH  (20 * CAMTRACK_LEN)


#ifdef __cplusplus
extern "C" {
#endif


static long sStartTick = 0;
static long sTick = 0;

static int  action_idx = 0;

M3D::World *world;
M3D::Camera *camera = NULL;
M3D::Model *model = NULL;
M3D::Light *light = NULL;
static GLfloat pos[4] = {0.0f, 10.0f, 20.0f, 1.0f};


M3D::Model *model_eyebrow_l = NULL;


///////////////////////////////////////////////////////////////////////////////

// Called from the app framework.
void appInit(int width, int height)
{
	world = new M3D::World ();
	world->setBgColor (0.0, 255.0, 0.0, 0.0); 
	world->setSize (320, 430);
	world->init ();

    camera = new M3D::Camera ();

#ifdef QUAD
    camera->setEye (0.0f, 0.0f, 55.0f); //for quad
#else
    camera->setEye (-3.0f, 15.0f, 15.0f);
#endif

    world->setCamera (camera);

    light = new M3D::Light();
    light->setPosition(pos);
    world->setLight(light);

#ifdef QUAD

    model = new M3D::Model ();
    model->setMeshCount (MESH_NUM);

    //init first triangle
    model->setTriangleNums(4, 0);
    model->setVertices(vertices0, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
    model->setIndices(indices, 4 * 3 * sizeof(GLshort), 0);
    //model->setColors(colors, VERTEX_NUM * 4 * sizeof(GLubyte), 0);


    //model->setNormals (normals, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
    model->setMaterialAmbient (0.9, 0.6, 0.6, 0);
    model->setMaterialDiffuse (0.9, 0.6, 0.6, 0);

//  model->setMaterialEmission (0.9, 0.9, 0.9, 1.0);
//    model->setMaterialShininess (1, 0);
//    model->setMaterialSpecular (0.9, 0.9, 0.9, 1.0);

#else


	model_eyebrow_l = new M3D::Model ();
    model_eyebrow_l->setMeshCount (EYEBROW_L_MESH_NUM);

    //init first triangle
    model_eyebrow_l->setTriangleNums(EYEBROW_L_TRIANGLE_NUM, 0);
    model_eyebrow_l->setVertices(afVertices_eyebrow_l, EYEBROW_L_VERTEX_NUM * 3 * sizeof(GLfloat), 0);
    model_eyebrow_l->setIndices(afVertIndices_eyebrow_l, EYEBROW_L_TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
    //model->setColors(colors, VERTEX_NUM * 4 * sizeof(GLubyte), 0);


    //model->setNormals (normals, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
    model_eyebrow_l->setMaterialAmbient (0.0, 0.0, 0.0, 0);
    model_eyebrow_l->setMaterialDiffuse (0.0, 0.0, 0.0, 0);
#endif

}


// Called from the app framework.
void appDeinit()
{
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

#ifdef QUAD
	model->renderModel ();
#else
	model_eyebrow_l->renderModel ();
#endif

	world->finishRender ();


}

void appSetModelTextureOffset (float x, float y, float z) {


    //LOGD ("appSetModelTextureOffset: x=%f, y=%f, z=%f\n", x, y, z);


}


void appSetModelRotate (float x, float y, float z) {


}

void appSetModelScale (float x, float y, float z) {


}

void appSetModelPosition (float x, float y, float z) {


}
/*
void fontRender (int x, int y, const char *string) {

}
*/

#ifdef __cplusplus
}
#endif

