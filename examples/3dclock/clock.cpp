
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
#define WINDOW_H    500

#define MESH_NUM 1

using namespace M3D;

World *world = NULL;
Camera *camera = NULL;
Model *model = NULL;
ImageTGA *image = NULL;


Model *model_pointer = NULL;
ImageTGA *image_pointer = NULL;
float angle = 0.0;
bool counter = false;   

Model *model_pointer_small = NULL;
ImageTGA *image_pointer_small = NULL;
float angle_small = 0.0;
bool counter_small = false;   


void display(){
 
	world->prepareRender ();

	model->renderModel ();
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

	model_pointer->setRotate (0.0, 0.0, angle);
	model_pointer->renderModel ();


	if (counter_small) {
		angle_small = angle_small - 0.1;
		if (angle_small <= -60.0)
        	counter_small = false;
	}
	else {
		angle_small = angle_small + 0.1;
		if (angle_small >= 10.0)
        	counter_small = true;

	}

	model_pointer_small->setPosition (-0.16, -0.4, 0.0);
	model_pointer_small->setRotate (0.0, 0.0, angle_small);
	model_pointer_small->renderModel ();


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
	Texture *texture = image->loadTexture ("res/clock.tga");


	model = new Model ();
	model->setMeshCount (MESH_NUM);

    model->setVertices(afVertices, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model->setTriangleNums(TRIANGLE_NUM, 0);
	if (texture != NULL)
		model->setTextureId (texture->textureId, 0);

	//model->setScale (0.5f, 0.5f, 0.5f);

	image_pointer = new ImageTGA ();
	Texture *texture_pointer = image->loadTexture ("res/pointer.tga");


	model_pointer = new Model ();
	model_pointer->setMeshCount (MESH_NUM);

    model_pointer->setVertices(afVerticesPointer, VERTEX_NUM_POINTER * 3 * sizeof(GLfloat), 0);
   	model_pointer->setIndices(afVertIndicesPointer, TRIANGLE_NUM_POINTER * 3 * sizeof(GLshort), 0);
	model_pointer->setUvs(afTexCoordPointer, VERTEX_NUM_POINTER * 2 * sizeof (GLfloat), 0);
    model_pointer->setTriangleNums(TRIANGLE_NUM_POINTER, 0);
	if (texture_pointer != NULL)
		model_pointer->setTextureId (texture_pointer->textureId, 0);


	image_pointer_small = new ImageTGA ();
	Texture *texture_pointer_small = image->loadTexture ("res/pointer_small.tga");

	model_pointer_small = new Model ();
	model_pointer_small->setMeshCount (MESH_NUM);

    model_pointer_small->setVertices(afVerticesPointerSmall, VERTEX_NUM_POINTER_SMALL * 3 * sizeof(GLfloat), 0);
   	model_pointer_small->setIndices(afVertIndicesPointerSmall, TRIANGLE_NUM_POINTER_SMALL * 3 * sizeof(GLshort), 0);
	model_pointer_small->setUvs(afTexCoordPointerSmall, VERTEX_NUM_POINTER_SMALL * 2 * sizeof (GLfloat), 0);
    model_pointer_small->setTriangleNums(TRIANGLE_NUM_POINTER_SMALL, 0);
	if (texture_pointer_small != NULL)
		model_pointer_small->setTextureId (texture_pointer_small->textureId, 0);



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


