
#ifdef MAC
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <mobile3d/m3d.h>
#include <mobile3d/world.h>
#include <mobile3d/camera.h>
#include <mobile3d/model.h>
#include <mobile3d/imageBMP.h>


#define WINDOW_W    500
#define WINDOW_H    500

#define MESH_NUM 1
/*
#define GRID_WIDTH       2
#define GRID_HEIGHT      2
#define TILE_COUNT_LINE  1
#define TILE_COUNT_COL   1 
*/
#define GRID_WIDTH       9
#define GRID_HEIGHT      9
#define TILE_COUNT_LINE  2
#define TILE_COUNT_COL   2


#define VERTEX_COUNT  ((GRID_WIDTH-1) * (GRID_HEIGHT-1) * 6)
#define TRIANGLE_COUNT  ((GRID_WIDTH-1) * (GRID_HEIGHT-1) * 2)

//#define VERTEX_COUNT  24
//#define TRIANGLE_COUNT  8

using namespace M3D;

World *world = NULL;
Camera *camera = NULL;
Model *model = NULL;
ImageBMP *image = NULL;

float points [GRID_WIDTH][GRID_HEIGHT][3] = {0};
float *vertices = NULL;
float *uvs = NULL;
//float vertices [VERTEX_COUNT * 3] = 0;
//float uvs [VERTEX_COUNT * 2] = 0;
int i = 0, j = 0;
float hold = 0.0f;
int wiggle_count = 0;

void display(){

	float float_x, float_y, float_xb, float_yb;

	for (int x = 0; x < GRID_WIDTH - 1; x++){
		for (int y = 0; y < GRID_HEIGHT - 1; y++){

			float_x = float(x) / float(GRID_WIDTH - 1);
			float_y = float(y) / float(GRID_HEIGHT - 1);
			float_xb = float(x+1) / float(GRID_WIDTH - 1);
			float_yb = float(y+1) / float(GRID_HEIGHT - 1);

/*
			float_x = x / (GRID_WIDTH - 1);
			float_y = y / (GRID_HEIGHT - 1);
			float_xb = (x+1) / (GRID_WIDTH - 1);
			float_yb = (y+1) / (GRID_HEIGHT - 1);
*/

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

	for (int k = 0; k < VERTEX_COUNT * 3; k++) {
		printf ("vertex[%d] = %f.\n", k, vertices[k]);
	}
	printf ("vertex count = %d, triangle count = %d.\n", VERTEX_COUNT, TRIANGLE_COUNT);


    model->setVertices(vertices, VERTEX_COUNT * 3 * sizeof(GLfloat), 0);
	model->setUvs(uvs, VERTEX_COUNT * 2 * sizeof (GLfloat), 0);
    model->setTriangleNums(TRIANGLE_COUNT, 0);
	//model->setScale (2.0f, 2.0f, 2.0f);
	model->setPosition (-2.0f, 0.0f, 0.0f);
	model->setRotate (90.0f, -10.0f, 0.0f);
 
	world->prepareRender ();
	model->renderModel ();
	world->finishRender ();

	//glFlush();
	glutSwapBuffers();

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

void init(){

	world = new World ();
	world->setSize (WINDOW_W, WINDOW_H);
	world->init ();

	camera = new Camera ();
	camera->setEye (0.0f, 0.0f, 5.0f);
	
	world->setCamera (camera);

	image = new ImageBMP ();
	Texture *texture = image->loadTexture ("/usr/local/share/mobile3d/sea/water.bmp");

	for (int x = 0; x < GRID_WIDTH; x++) {
		for (int y = 0; y < GRID_HEIGHT; y++) {
			//points[x][y][0] = x;
			//points[x][y][1] = y;
			points[x][y][0] = (float)x / (float)TILE_COUNT_LINE;
			points[x][y][1] = (float)y / (float)TILE_COUNT_COL;
			//points[x][y][2] = (float)sin( points[x][y][0] * points[x][y][0]);
			points[x][y][2] = 0.05 * (float)sin(((points[x][y][0] * 90.0f)/360.0f)*3.141592654 * 2.0f);
			printf ("points[%d][%d][0] = %f.\n", x, y, points[x][y][0]);
			printf ("points[%d][%d][1] = %f.\n", x, y, points[x][y][1]);
		}
	}

	model = new Model ();
	model->setMeshCount (MESH_NUM);
/*
    model->setVertices(afVertices, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model->setTriangleNums(TRIANGLE_NUM, 0);
*/
	if (texture != NULL)
		model->setTextureId (texture->textureId, 0);


	//model->setScale (0.5f, 0.5f, 0.5f);

	vertices = (float*)malloc (VERTEX_COUNT * 3 * sizeof (float));
	uvs =  (float*)malloc (VERTEX_COUNT * 2 * sizeof (float));


}

void keyboard(unsigned char key, int x, int y){
  switch(key) {
    case 'q': case 'Q': case 27:
      exit(0);
      break;
  }
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  	glutInitWindowSize(WINDOW_W, WINDOW_H);
  	glutInitWindowPosition(0,0);
  	glutCreateWindow("simple");
  	glutDisplayFunc(display);
	glutIdleFunc(display);
  	glutKeyboardFunc(keyboard);
  	init();
  	glutMainLoop();
	FREEANDNULL (world);
	FREEANDNULL (camera);
	FREEANDNULL (model);
	FREEANDNULL (vertices);
	FREEANDNULL (uvs);
  	return 0;
}


