
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <mobile3d/m3d.h>
#include <mobile3d/world.h>
#include <mobile3d/camera.h>

#include "skydome.h"

#define WINDOW_W    800
#define WINDOW_H    600

using namespace M3D;

World *world = NULL;
Camera *camera = NULL;
float angle = 0.0f;
Skydome *skydome = NULL;

void display(){
 
	world->prepareRender ();
	skydome->RenderSkyDome(0.0f, 0.0f, 0.0f);
	world->finishRender ();

	glFlush();
}

void init(){

	world = new World ();
	world->setSize (WINDOW_W, WINDOW_H);
	world->init ();

	camera = new Camera ();
   	camera->setEye(60.0f, 30.0f, 60.0f);
   	camera->setCenter(0.0f, 15.0f, 0.0f);

	
	world->setCamera (camera);

	
	skydome = new Skydome();
	skydome->GenerateDome(256, 30.0f, 10.0f, 64.0f, 64.0f);
	

	
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


    case 'j': case 'J':
	camera->yaw (1.0f);
        glutPostRedisplay();

      break;

    case 'l': case 'L':
	camera->yaw (-1.0f);
        glutPostRedisplay();



    case 's': case 'S':
        camera->move (0.0f, 0.0f, 1.0f);
        glutPostRedisplay();

      break;

    case 'w': case 'W':
        camera->move (0.0f, 0.0f, -1.0f);
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
	//glutIdleFunc(display);
  	glutKeyboardFunc(keyboard);
  	init();
  	glutMainLoop();
	FREEANDNULL (world);
	FREEANDNULL (camera);
  	return 0;
}


