
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


#define WINDOW_W   1024 
#define WINDOW_H   768 

#define MESH_NUM 1

//#define LOGO 1

using namespace M3D;

World *world = NULL;
Camera *camera = NULL;
ModelAM *model = NULL;
Light *light = NULL;
static GLfloat pos[4] = {10.0f, 40.0f, 80.0f, 1.0f};

static int startx = 0, starty = 0;
static GLfloat angle_x = 0;   /* in degrees */
static GLfloat angle_y = 0;   /* in degrees */


ImageBMP *image = NULL;

#define MAX_CAR_NUM 24 
const char * file_name [MAX_CAR_NUM] = {

        "/usr/local/share/mobile3d/audi/axle.am",
        "/usr/local/share/mobile3d/audi/black.am",
        "/usr/local/share/mobile3d/audi/glass.am",
        "/usr/local/share/mobile3d/audi/mirror.am",
        "/usr/local/share/mobile3d/audi/pipe.am",
        "/usr/local/share/mobile3d/audi/tires.am",
        "/usr/local/share/mobile3d/audi/hub.am",
        "/usr/local/share/mobile3d/audi/inside.am",
        "/usr/local/share/mobile3d/audi/body.am",
        "/usr/local/share/mobile3d/audi/windowBackFrame.am",
        "/usr/local/share/mobile3d/audi/windowBlack.am",
        "/usr/local/share/mobile3d/audi/windowFrame.am",
        "/usr/local/share/mobile3d/audi/windowFrontFrame.am",
        "/usr/local/share/mobile3d/audi/windowFrontRubber.am",
        "/usr/local/share/mobile3d/audi/airInlet.am",
        "/usr/local/share/mobile3d/audi/airInletFrame.am",
        "/usr/local/share/mobile3d/audi/lightBack.am",
        "/usr/local/share/mobile3d/audi/lightBox.am",
        "/usr/local/share/mobile3d/audi/lightGlassBig.am",
        "/usr/local/share/mobile3d/audi/lightGlassSmall.am",
        "/usr/local/share/mobile3d/audi/lightTube.am",
        "/usr/local/share/mobile3d/audi/lightFront.am",
        "/usr/local/share/mobile3d/audi/logo.am",
        "/usr/local/share/mobile3d/audi/number.am",

};



/*
#define MAX_CAR_NUM 15
const char * file_name [MAX_CAR_NUM] = {
        "/usr/local/share/mobile3d/audi/bremse_back_left.am",
        "/usr/local/share/mobile3d/audi/bremse_back_right.am",
        "/usr/local/share/mobile3d/audi/bremse_front_left.am",
        "/usr/local/share/mobile3d/audi/bremse_front_right.am",
        "/usr/local/share/mobile3d/audi/inside.am",
        "/usr/local/share/mobile3d/audi/wheel_front_left.am",
        "/usr/local/share/mobile3d/audi/wheel_front_right.am",
        "/usr/local/share/mobile3d/audi/wheel_back_left.am",
        "/usr/local/share/mobile3d/audi/wheel_back_right.am",
        "/usr/local/share/mobile3d/audi/middle_frame_four_wheel.am",
        "/usr/local/share/mobile3d/audi/frame.am",
        "/usr/local/share/mobile3d/audi/edge_frame_enginecover_backbox.am",
        "/usr/local/share/mobile3d/audi/front_net_light.am",
        "/usr/local/share/mobile3d/audi/logo.am",
        "/usr/local/share/mobile3d/audi/light.am",
};
*/

ModelAM **models = NULL;

void display(){

	world->prepareRender ();
#ifdef LOGO
	model->setRotate (angle_x, angle_y, 0.0); 
	model->renderModel ();
#else
	int i = 0;
	for (i = 0; i < MAX_CAR_NUM; i++)
	{
		models[i]->setRotate (angle_x, angle_y, 0.0); 
		glEnable (GL_MULTISAMPLE_ARB);
		models[i]->renderModel ();
		glDisable (GL_MULTISAMPLE_ARB);

	}
#endif
	world->finishRender ();

	glFlush();
	glutSwapBuffers ();	
}

void init(){

	world = new World ();
	world->setBgColor (0.0, 1.0, 1.0, 0.0);
	world->setSize (WINDOW_W, WINDOW_H);
	world->init ();

	camera = new Camera ();
	camera->setEye (0.0f, 0.0f, 185.0f);
	
	world->setCamera (camera);

    light = new Light();
    light->setPosition(pos);
    world->setLight(light);

#ifdef LOGO
	model = new ModelAM ();
	model->setMeshCount (MESH_NUM);
	model->loadModel (file_name[0]);
	//model->loadModel ("/usr/local/share/mobile3d/audi/logo.am");
#else

	image = new ImageBMP ();
	Texture *texture = image->loadTexture ("/usr/local/share/mobile3d/audi/plate.bmp");
//	Texture *texture = image->loadTexture ("/usr/local/share/mobile3d/audi/a6-main-body-color.bmp");

	models = (ModelAM**)malloc (MAX_CAR_NUM * sizeof (ModelAM*));
	for (int i = 0; i < MAX_CAR_NUM; i++){
		models[i] = new ModelAM ();
		models[i]->setMeshCount (MESH_NUM);
		models[i]->loadModel (file_name[i]);
//		models[i]->setScale (0.4, 0.4, 0.4);
		if (i == 23)
			models[i]->setTextureId (texture->textureId);
	}
#endif

} 

void keyboard(unsigned char key, int x, int y){ 
	switch(key) 
	{ 


    	case 'i': case 'I':
    		camera->pitch (1.0f);
        	glutPostRedisplay();
      		break;

    	case 'k': case 'K':
    		camera->pitch (-1.0f);
        	glutPostRedisplay();
      		break;

    	case 'f': case 'F':
			angle_x = -90.0f;
			angle_y = 0.0f;
      		break;


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

  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
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

#ifdef LOGO
	FREEANDNULL (model);
#else

	for (int i = 0; i < MAX_CAR_NUM; i++){
		delete(models[i]);
	}
	FREEANDNULL (models);




#endif

  	return 0;
}


