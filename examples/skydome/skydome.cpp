
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <mobile3d/m3d.h>
#include <mobile3d/world.h>
#include <mobile3d/camera.h>
#include <mobile3d/model.h>
#include <mobile3d/imageBMP.h>
#include <mobile3d/M3DSkydome.h>
#include "data.h"

#define WINDOW_W    500
#define WINDOW_H    500

using namespace M3D;

World *world = NULL;
Camera *camera = NULL;
Model *model = NULL;
Skydome *skydome = NULL;
ImageBMP *image = NULL;
float angle = 0.0f;

void display(){
 
	world->prepareRender ();
//	model->renderModel ();
	skydome->setRotate(-90.0f, 0.0f, angle);
	skydome->renderModel ();
	world->finishRender ();

	glFlush();
}

void init(){

	world = new World ();
	world->setSize (WINDOW_W, WINDOW_H);
	world->init ();

	camera = new Camera ();
//	camera->setEye (0.0f, 0.0f, 5.0f);


    	camera->setEye(60.0f, 30.0f, 60.0f);
    	camera->setCenter(0.0f, 15.0f, 0.0f);

	
	world->setCamera (camera);
/*
	model = new Model ();
	model->setMeshCount (MESH_NUM);

    //init second triangle
    model->setVertices(vertices0, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
    model->setColors(colors, VERTEX_NUM * 4 * sizeof(GLubyte), 0);
    model->setTriangleNums(1, 0);
*/

	skydome = new Skydome(128, 30.0f, 10.0f);
	image = new ImageBMP ();
	Texture *texture = image->loadTexture ("/usr/local/share/mobile3d/skydome/clouds.bmp");
	skydome->setTextureId (texture->textureId);
	//skydome->setRotate(90.0f, 0.0f, 0.0f);
	

	
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
	//glutIdleFunc(display);
  	glutKeyboardFunc(keyboard);
  	init();
  	glutMainLoop();
	FREEANDNULL (world);
	FREEANDNULL (camera);
	FREEANDNULL (model);
  	return 0;
}


