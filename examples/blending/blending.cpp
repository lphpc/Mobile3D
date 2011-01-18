
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <mobile3d/m3d.h>
#include <mobile3d/world.h>
#include <mobile3d/camera.h>
#include <mobile3d/model.h>
#include <mobile3d/imageRGB.h>
#include "data.h"


#define WINDOW_W    500
#define WINDOW_H    500

#define MESH_NUM 1

using namespace M3D;

World *world = NULL;
Camera *camera = NULL;
Model *model = NULL;
ImageRGB *imageRGB = NULL;

Texture *texture_bottom = NULL;
Texture *texture_top = NULL;

void display(){
 
	world->prepareRender ();


	if (texture_bottom != NULL) { 
		model->setTextureId (texture_bottom->textureId, 0);
		model->enableBlend (false, 0);
		model->renderModel ();
	}


	if (texture_top != NULL) {
		model->setTextureId (texture_top->textureId, 0);
		model->enableBlend (true, 0);
		model->setBlendFunc (GL_ZERO, GL_SRC_COLOR, 0);
		model->renderModel ();
	}



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

	imageRGB = new ImageRGB ();
	texture_bottom = imageRGB->loadRGBTexture ("/usr/local/share/mobile3d/blending/floor.rgb");
	texture_top = imageRGB->loadAlphaTexture ("/usr/local/share/mobile3d/blending/caust00.bw");
	if (texture_top == NULL)
		printf ("Failed to load rgb.\n");


	model = new Model ();
	model->setMeshCount (MESH_NUM);

    model->setVertices(afVertices, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model->setTriangleNums(TRIANGLE_NUM, 0);
/*
	if (texture_bottom != NULL)
		model->setTextureId (texture_top->textureId, 0);
*/

	//model->setScale (0.5f, 0.5f, 0.5f);


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
  	glutKeyboardFunc(keyboard);
  	init();
  	glutMainLoop();
	FREEANDNULL (world);
	FREEANDNULL (camera);
	FREEANDNULL (model);
  	return 0;
}


