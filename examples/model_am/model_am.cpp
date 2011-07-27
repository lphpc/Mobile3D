
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
#include <mobile3d/model_am.h>
#include <mobile3d/imageBMP.h>


#define WINDOW_W    500
#define WINDOW_H    500

#define MESH_NUM 1

using namespace M3D;

World *world = NULL;
Camera *camera = NULL;
ModelAM *model = NULL;
Light *light = NULL;
static GLfloat pos[4] = {5.0f, 0.0f, 30.0f, 1.0f};

static int startx = 0, starty = 0;
static GLfloat angle_x = 0;   /* in degrees */
static GLfloat angle_y = 0;   /* in degrees */


void display(){

	model->setRotate (angle_x, angle_y, 0.0); 
	world->prepareRender ();
	model->renderModel ();
	world->finishRender ();

	glFlush();
	glutSwapBuffers ();	
}

void init(){

	world = new World ();
	world->setBgColor (0.0, 0.0, 0.0, 0.0);
	world->setSize (WINDOW_W, WINDOW_H);
	world->init ();

	camera = new Camera ();
	camera->setEye (0.0f, 0.0f, 55.0f);
	
	world->setCamera (camera);

    light = new Light();
    light->setPosition(pos);
    world->setLight(light);


	model = new ModelAM ();
	model->setMeshCount (MESH_NUM);
	model->loadModel ("/usr/local/share/mobile3d/model_am/quad.am");

} 

void keyboard(unsigned char key, int x, int y){ 
	switch(key) 
	{ 
		case 'q': 
		case 'Q': 
		case 27: 
			exit(0); 
			break;
  	}
}

void processMouse(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) {
    	if (state == GLUT_DOWN) {
			printf ("mouse left button is pressed.\n");
      		startx = x;
      		starty = y;
    	}
    	if (state == GLUT_UP) {
			printf ("mouse left button is released.\n"); 
		} 
	} 

}

void processMouseActiveMotion(int x, int y) {

	printf ("Mouse is moving. \n");
	angle_y = angle_y + (x - startx);
	angle_x = angle_x + (y - starty);
	startx = x;
	starty = y;
	glutPostRedisplay();

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
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);
	

  	init();

  	glutMainLoop();

	FREEANDNULL (world);
	FREEANDNULL (camera);
	FREEANDNULL (model);

  	return 0;
}


