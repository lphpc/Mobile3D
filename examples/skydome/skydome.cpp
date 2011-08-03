
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
#include <mobile3d/M3DSkydome.h>
#include <mobile3d/M3DSkydomeTexture.h>
#include "data.h"

#define WINDOW_W    800
#define WINDOW_H    600

using namespace M3D;

//#define SKYDOMETEXTURE 1

World *world = NULL;
Camera *camera = NULL;
Model *model = NULL;

#ifdef SKYDOMETEXTURE
SkydomeT *skydome = NULL;
#else
Skydome *skydome = NULL;
#endif

ImageBMP *image = NULL;
float angle = 0.0f;

void display(){
 
	world->prepareRender ();
//	model->renderModel ();

#ifdef SKYDOMETEXTURE
	skydome->setRotate(-90.0f, 0.0f, angle);
	skydome->renderModel ();
#else
	skydome->renderModel ();
#endif

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

#ifdef SKYDOMETEXTURE 
	skydome = new SkydomeT(256, 30.0f, 10.0f);
	//skydome = new Skydome(128, 30.0f, 10.0f);
	image = new ImageBMP ();
	Texture *texture = image->loadTexture ("/usr/local/share/mobile3d/skydome/clouds.bmp");
	skydome->setTextureId (texture->textureId);
	skydome->setRotate(90.0f, 0.0f, 0.0f);
#else
	skydome = new Skydome();
	skydome->GenerateDome(256, 30.0f, 10.0f, 64.0f, 64.0f);

#endif	

	
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
        camera->move (0.0f, 0.0f, 10.0f);
        glutPostRedisplay();

      break;

    case 'w': case 'W':
        camera->move (0.0f, 0.0f, -10.0f);
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
	FREEANDNULL (model);
	delete (skydome);

  	return 0;
}


