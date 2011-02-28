
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <mobile3d/m3d.h>
#include <mobile3d/world.h>
#include <mobile3d/camera.h>
#include <mobile3d/model.h>
#include "data.h"


#define USEVBO 1
#define USEINDEX 1

#define WINDOW_W    500
#define WINDOW_H    500

using namespace M3D;

World *world = NULL;
Camera *camera = NULL;
Model *model = NULL;


void display(){
 
	world->prepareRender ();

	model->renderModel ();

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

	model = new Model ();
	model->setMeshCount (MESH_NUM);

#ifdef USEVBO
    //init first triangle
	size_t sizeInBytesVertex = VERTEX_NUM * 3 * sizeof(GLfloat) + VERTEX_NUM * 4 * sizeof(GLubyte);
    size_t sizeInBytesIndex = 1 * 3 * sizeof(GLfloat);	
	model->createVBO (sizeInBytesVertex, sizeInBytesIndex, 0);
#endif

    model->setVertices(vertices0, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
#ifdef USEINDEX
    model->setIndices(indices0, 1 * 3 * sizeof(GLshort), 0);
#endif
    model->setColors(colors, VERTEX_NUM * 4 * sizeof(GLubyte), 0);
    model->setTriangleNums(1, 0);

	//init second triangle

#ifdef USEVBO
	model->createVBO (sizeInBytesVertex, sizeInBytesIndex, 1);
#endif

    model->setVertices(vertices1, VERTEX_NUM * 3 * sizeof(GLfloat), 1);

#ifdef USEINDEX
    model->setIndices(indices1, 1 * 3 * sizeof(GLshort), 1);
#endif 

    model->setColors(colors, VERTEX_NUM * 4 * sizeof(GLubyte), 1);
    model->setTriangleNums(1, 1);

#ifdef RENDERER
	renderer = new M3DRenderer ();
#endif


}

void keyboard(unsigned char key, int x, int y){
	switch(key) {
    	case 'q': case 'Q': case 27:
#ifdef USEVBO
		model->destroyVBO ();
#endif
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
#ifdef RENDERER
	FREEANDNULL (renderer);
#endif

  	return 0;
}


