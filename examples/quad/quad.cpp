
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <mobile3d/m3d.h>
#include <mobile3d/world.h>
#include <mobile3d/camera.h>
#include <mobile3d/imageBMP.h>
#include <mobile3d/M3DQuad.h>

#define GRID 1

#define WINDOW_W    500
#define WINDOW_H    500


using namespace M3D;

#define GRID_COUNT 24
#define MARGIN 2.0

World *world = NULL;
Camera *camera = NULL;


static int startx = 0, starty = 0;
static GLfloat angle_x = 0;   /* in degrees */
static GLfloat angle_y = 0;   /* in degrees */


#ifdef GRID
M3DQuad *quadGrid[GRID_COUNT];
#else
M3DQuad *quad = NULL;
#endif

#ifdef GRID
void initGrid ()
{
	for (int i = 0; i < GRID_COUNT; i++){
		quadGrid[i] = new M3DQuad ();
		quadGrid[i]->create ((float)(i/4) - 1.5, (float)(i%4) - 0.8, 0.9, 0.9, 
				"/usr/local/share/mobile3d/quad/camelback-mountain.tga");
	}	
}

void drawGrid ()
{
	for (int i = 0; i < GRID_COUNT; i++){
		
		quadGrid[i]->rotate (angle_x, angle_y, 0.0);
		quadGrid[i]->draw ();
	}
}

void destroyGrid ()
{
	for (int i = 0; i < GRID_COUNT; i++){
		FREEANDNULL (quadGrid[i]);
	}

}
#endif

void display(){

	world->prepareRender ();

#ifdef GRID
	drawGrid ();
#else
	quad->draw ();
#endif

	world->finishRender ();

	glFlush();
}

void init(){

	world = new World ();
	world->setBgColor (0.0, 0.0, 0.0, 0.0);
	world->setSize (WINDOW_W, WINDOW_H);
	world->init ();

	camera = new Camera ();
	camera->setEye (0.0f, 0.0f, 5.0f);
	
	world->setCamera (camera);

#ifdef GRID
	initGrid ();
#else
	quad = new M3DQuad ();
	quad->create (-1.0, 1.0, 2.0, 2.0, "/usr/local/share/mobile3d/quad/camelback-mountain.tga");
#endif

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

  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
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

#ifdef GRID
	destroyGrid ();
#else
	FREEANDNULL (quad);
#endif


  	return 0;
}


