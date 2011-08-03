
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
	camera->setEye (0.0f, 0.0f, 10.0f); 
	world->setCamera (camera);

	image = new ImageTGA ();
	Texture *texture = image->loadTexture ("/usr/local/share/mobile3d/map/map_small.tga");


	model = new Model ();
	model->setMeshCount (MESH_NUM);

    model->setVertices(afVertices, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model->setTriangleNums(TRIANGLE_NUM, 0);
	if (texture != NULL)
		model->setTextureId (texture->textureId, 0);


	model->setScale (15.0f, 15.0f, 0.0f);


}

void keyboard(unsigned char key, int x, int y){
  switch(key) {


    case 'i': case 'I':
	camera->pitch (1.0f);
        glutPostRedisplay();

      break;

    case 'k': case 'K':
	camera->pitch (-1.0f);
        glutPostRedisplay();

      break;


    case 'a': case 'A':
	camera->yaw (1.0f);
        glutPostRedisplay();

      break;

    case 'd': case 'D':
	camera->yaw (-1.0f);
        glutPostRedisplay();

      break;



    case 'w': case 'W': 

	camera->move (0.0f, 0.0f, -0.1f);
        glutPostRedisplay();

      break;

    case 's': case 'S': 
	camera->move (0.0f, 0.0f, 0.1f);
        glutPostRedisplay();


    case 'j': case 'J': 

	camera->moveRelative (0.0f, -0.1f, 0.0f);
        glutPostRedisplay();

      break;

    case 'l': case 'L': 
	camera->moveRelative (0.0f, 0.1f, 0.0f);
        glutPostRedisplay();


      break;






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


