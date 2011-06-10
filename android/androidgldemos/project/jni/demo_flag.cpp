
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLES/gl.h> /* For NDK*/
#include <assert.h>
#include <android/log.h>

#include "app.h"

#define MESH_NUM 1

// Total run length is 20 * camera track base unit length (see cams.h).
#define RUN_LENGTH  (20 * CAMTRACK_LEN)


#define GRID_WIDTH       9
#define GRID_HEIGHT      9
#define TILE_COUNT_LINE  2
#define TILE_COUNT_COL   2


#define VERTEX_COUNT  ((GRID_WIDTH-1) * (GRID_HEIGHT-1) * 6)
#define TRIANGLE_COUNT  ((GRID_WIDTH-1) * (GRID_HEIGHT-1) * 2)



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


static float points [GRID_WIDTH][GRID_HEIGHT][3] = {0};
static float *vertices = NULL;
static float *uvs = NULL;

static int i = 0;
static int j = 0;
static float hold = 0.0f;
static int wiggle_count = 0;


///////////////////////////////////////////////////////////////////////////////

// Called from the app framework.
void appInitFlag(int width, int height)
{
	world = new M3D::World ();
	world->setSize (320, 430);
	world->init ();

    camera = new M3D::Camera ();
    camera->setEye (0.0f, 0.0f, 5.0f);

    world->setCamera (camera);

    image = new M3D::ImageBMP ();
    Texture *texture = image->loadTexture ("/data/mobile3d/androidgldemos/flag/tim.bmp");

    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            points[x][y][0] = (float)x / (float)TILE_COUNT_LINE;
            points[x][y][1] = (float)y / (float)TILE_COUNT_COL;
            points[x][y][2] = 0.2f * (float)sin(((points[x][y][0] * 90.0f)/360.0f)*3.141592654 * 2.0f);
            //points[x][y][2] = 0.1f * (float)sin(((points[x][y][0] * 90.0f)/360.0f)*3.141592654 * 2.0f);
        }
    }


    model = new M3D::Model ();
    model->setMeshCount (MESH_NUM);

    if (texture != NULL)
        model->setTextureId (texture->textureId, 0);

	vertices = (float*)malloc (VERTEX_COUNT * 3 * sizeof (float));
	uvs =  (float*)malloc (VERTEX_COUNT * 2 * sizeof (float));


}


// Called from the app framework.
void appDeinitFlag()
{

    FREEANDNULL (vertices);
    FREEANDNULL (uvs);
    FREEANDNULL (model);
    FREEANDNULL (camera);
    FREEANDNULL (world);
	
}

// Called from the app framework.
/* The tick is current time in milliseconds, width and height
 * are the image dimensions to be rendered.
 */
void appRenderFlag(long tick, int width, int height)
{
    if (sStartTick == 0)
        sStartTick = tick;

    // Actual tick value is "blurred" a little bit.
    sTick = (sTick + tick - sStartTick) >> 1;

    float float_x, float_y, float_xb, float_yb;

	for (int x = 0; x < GRID_WIDTH - 1; x++){
		for (int y = 0; y < GRID_HEIGHT - 1; y++){

			float_x = float(x) / float(GRID_WIDTH - 1);
			float_y = float(y) / float(GRID_HEIGHT - 1);
			float_xb = float(x+1) / float(GRID_WIDTH - 1);
			float_yb = float(y+1) / float(GRID_HEIGHT - 1);


			//triangle 1
			uvs [j++] = float_x;
			uvs [j++] = float_y;
			vertices [i++] = points [x][y][0];
			vertices [i++] = points [x][y][1];
			vertices [i++] = points [x][y][2];

			uvs [j++] = float_x;
			uvs [j++] = float_yb;
			vertices [i++] = points [x][y+1][0];
			vertices [i++] = points [x][y+1][1];
			vertices [i++] = points [x][y+1][2];

			uvs [j++] = float_xb;
			uvs [j++] = float_yb;
			vertices [i++] = points [x+1][y+1][0];
			vertices [i++] = points [x+1][y+1][1];
			vertices [i++] = points [x+1][y+1][2];

			//triangle 2
			uvs [j++] = float_xb;
			uvs [j++] = float_yb;
			vertices [i++] = points [x+1][y+1][0];
			vertices [i++] = points [x+1][y+1][1];
			vertices [i++] = points [x+1][y+1][2];

			uvs [j++] = float_xb;
			uvs [j++] = float_y;
			vertices [i++] = points [x+1][y][0];
			vertices [i++] = points [x+1][y][1];
			vertices [i++] = points [x+1][y][2];

			uvs [j++] = float_x;
			uvs [j++] = float_y;
			vertices [i++] = points [x][y][0];
			vertices [i++] = points [x][y][1];
			vertices [i++] = points [x][y][2];
	
		}
	}

    model->setVertices(vertices, VERTEX_COUNT * 3 * sizeof(GLfloat), 0);
	model->setUvs(uvs, VERTEX_COUNT * 2 * sizeof (GLfloat), 0);
    model->setTriangleNums(TRIANGLE_COUNT, 0);
	model->setPosition (-2.0f, -2.0f, 0.0f);

	world->prepareRender ();
	model->renderModel ();
	world->finishRender ();


	i = 0;
	j = 0;

	if (wiggle_count == 2) {
		for (int y = 0; y < GRID_HEIGHT; y++){
			hold = points[0][y][2];
			for (int x = 0; x < GRID_WIDTH - 1; x++) {
				points[x][y][2] = points[x+1][y][2];
			}
			points[GRID_WIDTH-1][y][2] = hold;
		}
		wiggle_count = 0;
	}
	wiggle_count++;


}

void appSetModelTextureOffsetFlag (float x, float y, float z) {


    //LOGD ("appSetModelFlagOffset: x=%f, y=%f, z=%f\n", x, y, z);


}


void appSetModelRotateFlag (float x, float y, float z) {


}

void appSetModelScaleFlag (float x, float y, float z) {


}

void appSetModelPositionFlag (float x, float y, float z) {


}
/*
void fontRender (int x, int y, const char *string) {

}
*/

#ifdef __cplusplus
}
#endif

