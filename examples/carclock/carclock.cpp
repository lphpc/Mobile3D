
#include <sys/time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <mobile3d/m3d.h>
#include <mobile3d/world.h>
#include <mobile3d/camera.h>
#include <mobile3d/model.h>
#include <mobile3d/imageTGA.h>
#include "data.h"


#define WINDOW_W    500
#define WINDOW_H    400

#define MESH_NUM 1

using namespace M3D;

World *world = NULL;
Camera *camera = NULL;
Model *model = NULL;
Model *model_r = NULL;
Model *model_f = NULL;
Model *model_oil = NULL;
ImageTGA *image = NULL;
ImageTGA *image_r = NULL;
ImageTGA *image_f = NULL;
ImageTGA *image_oil = NULL;


ImageTGA *image_pointer = NULL;
float angle = 0.0;
bool counter = false;   

Model *model_pointer_small = NULL;
ImageTGA *image_pointer_small = NULL;
float angle_small = 0.0;
bool counter_small = false;   


//get the ms unit time in Linux & Android
#define CLOCK(v_time) v_time.tv_sec * 1000 + v_time.tv_usec / 1000


static long int start_time = 0;
static struct timeval timeNow;

static long int duration = 1000; //ms
static long int elapse_time = 0;

static float oil_x = 0.0f;
static float oil_y = 0.0f;
static float oil_z = 0.0f;
static float oil_angle = 0.0f;

static float clock_angle_r = 0.0f;
static float clock_angle_l = 0.0f;

static bool enable_animation = false;

void display(){

	if(enable_animation) { 
		
    	gettimeofday(&timeNow, NULL);
		elapse_time = CLOCK(timeNow) - start_time;
		if (elapse_time < duration) {
			oil_x += 0.001f;
			oil_z -= 0.02f;
			oil_angle -= 0.5;
			clock_angle_r -= 0.2;
			clock_angle_l += 0.2;
			printf ("elapse %ld ms, duration = %ld.\n", elapse_time, duration);
		}
	} //end of enable_animation
	



	world->prepareRender ();

	model_f->renderModel ();

	if(enable_animation) { 
		model->setPosition (-2.8, 0.0f, -1.5f);
		model->setRotate (0.0f, clock_angle_l, 0.0f);
		model->setPosition2 (2.8, 0.0f, 1.5f);
	}
	model->renderModel ();


	if(enable_animation) { 
		model_r->setPosition (2.8, 0.0f, -1.5f);
		model_r->setRotate (0.0f, clock_angle_r, 0.0f);
		model_r->setPosition2 (-2.8, 0.0f, 1.5f);
	}
	model_r->renderModel ();


	//if disable animation, do not display pointer
	if (!enable_animation) {
		if (counter) {
			angle = angle - 0.1;
			if (angle <= -160.0)
        		counter = false;
		}
		else {
			angle = angle + 0.1;
			if (angle >= 100.0)
        		counter = true;

		}


		if (counter_small) {
			angle_small = angle_small - 0.1;
			if (angle_small <= -120.0)
        		counter_small = false;
		}
		else {
			angle_small = angle_small + 0.1;
			if (angle_small >= -60.0)
        		counter_small = true;

		}

		model_pointer_small->setPosition (-1.22, 0.0, 0.0);
		model_pointer_small->setRotate (0.0, 0.0, angle_small);
		model_pointer_small->renderModel ();

	}


	if(enable_animation) { 
		model_oil->setPosition (oil_x, oil_y, oil_z);
		model_oil->setRotate (0.0f, oil_angle, 0.0f);
	}

	model_oil->renderModel ();

	world->finishRender ();

	glFlush();
}

void init(){

	world = new World ();
	world->setSize (WINDOW_W, WINDOW_H);
	world->init ();

	camera = new Camera ();
	camera->setEye (0.0f, 0.0f, 5.0f);
	
	world->setCamera (camera);

	image = new ImageTGA ();
	Texture *texture = image->loadTexture ("/usr/local/share/mobile3d/carclock/left.tga");


	model = new Model ();
	model->setMeshCount (MESH_NUM);

    model->setVertices(afVertices, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model->setTriangleNums(TRIANGLE_NUM, 0);
	if (texture != NULL)
		model->setTextureId (texture->textureId, 0);

	//model->setScale (0.5f, 0.5f, 0.5f);



	image_pointer_small = new ImageTGA ();
	Texture *texture_pointer_small = image->loadTexture ("/usr/local/share/mobile3d/carclock/pointer_small.tga");

	model_pointer_small = new Model ();
	model_pointer_small->setMeshCount (MESH_NUM);

    model_pointer_small->setVertices(afVerticesPointerSmall, VERTEX_NUM_POINTER_SMALL * 3 * sizeof(GLfloat), 0);
   	model_pointer_small->setIndices(afVertIndicesPointerSmall, TRIANGLE_NUM_POINTER_SMALL * 3 * sizeof(GLshort), 0);
	model_pointer_small->setUvs(afTexCoordPointerSmall, VERTEX_NUM_POINTER_SMALL * 2 * sizeof (GLfloat), 0);
    model_pointer_small->setTriangleNums(TRIANGLE_NUM_POINTER_SMALL, 0);
	if (texture_pointer_small != NULL)
		model_pointer_small->setTextureId (texture_pointer_small->textureId, 0);


	image_r = new ImageTGA ();
	Texture *texture_r = image->loadTexture ("/usr/local/share/mobile3d/carclock/right.tga");


	model_r = new Model ();
	model_r->setMeshCount (MESH_NUM);

    model_r->setVertices(afVerticesR, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model_r->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model_r->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model_r->setTriangleNums(TRIANGLE_NUM, 0);
	if (texture_r != NULL)
		model_r->setTextureId (texture_r->textureId, 0);


	image_f = new ImageTGA ();
	Texture *texture_f = image->loadTexture ("/usr/local/share/mobile3d/carclock/floor.tga");

	model_f = new Model ();
	model_f->setMeshCount (MESH_NUM);

    model_f->setVertices(afVerticesF, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model_f->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model_f->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model_f->setTriangleNums(TRIANGLE_NUM, 0);
	if (texture_f != NULL)
		model_f->setTextureId (texture_f->textureId, 0);


	image_oil = new ImageTGA ();
	Texture *texture_oil = image->loadTexture ("/usr/local/share/mobile3d/carclock/oil.tga");


	model_oil = new Model ();
	model_oil->setMeshCount (MESH_NUM);

    model_oil->setVertices(afVerticesOil, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model_oil->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model_oil->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model_oil->setTriangleNums(TRIANGLE_NUM, 0);
	if (texture_oil != NULL)
		model_oil->setTextureId (texture_oil->textureId, 0);


}

void keyboard(unsigned char key, int x, int y){
  switch(key) {
    case 'q': case 'Q': case 27:
      exit(0);
      break;
    case 'r': case 'R': case 28:
		if (enable_animation) {
			enable_animation = false;

			clock_angle_l = 0.0f;
			clock_angle_r = 0.0f;

			model->setPosition (0.0f, 0.0f, 0.0f);
			model->setRotate (0.0f, 0.0f, 0.0f);
			model->setPosition2 (0.0f, 0.0f, 0.0f);

			model_r->setPosition (0.0f, 0.0f, 0.0f);
			model_r->setRotate (0.0f, 0.0f, 0.0f);
			model_r->setPosition2 (0.0f, 0.0f, 0.0f);

			oil_angle = 0.0;
			oil_x = 0.0f;
			oil_y = 0.0f;
			oil_z = 0.0f;

			model_oil->setPosition (0.0f, 0.0f, 0.0f);
			model_oil->setRotate (0.0f, 0.0f, 0.0f);


		}
		else {
			enable_animation = true;
    		gettimeofday(&timeNow, NULL);
			start_time = CLOCK(timeNow);
		}

      break;

  }
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
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
  	return 0;
}


