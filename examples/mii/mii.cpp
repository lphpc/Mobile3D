
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <mobile3d/m3d.h>
#include <mobile3d/world.h>
#include <mobile3d/camera.h>
#include <mobile3d/model_am.h>
#include <mobile3d/light.h>


#define WINDOW_W    500
#define WINDOW_H    500


using namespace M3D;

#ifdef __cplusplus
extern "C" {
#endif


World *world = NULL;
Camera *camera = NULL;
Light *light = NULL;
static GLfloat pos[4] = {0.0f, 10.0f, 20.0f, 1.0f};


ModelAM* model;

ModelAM*      model_body;
ModelAM*      model_head;
ModelAM*      model_hair;
ModelAM*      model_eyebrow_l;
ModelAM*      model_eyebrow_r;
ModelAM*      model_eye_l;
ModelAM*      model_eye_r;
ModelAM*      model_nose;
ModelAM*      model_mouth;

int startx = 0, starty = 0;
static GLfloat angle_x = 0;   /* in degrees */
static GLfloat angle_y = 0;   /* in degrees */


void display(){


	world->prepareRender ();

//	model->renderModel ();

/*
    model_body->renderModel();
*/
/*
    model_head->renderModel();
*/

    model_hair->renderModel();
    model_eyebrow_l->renderModel();
    model_eyebrow_r->renderModel();
    model_eye_l->renderModel();
    model_eye_r->renderModel();
    model_nose->renderModel();
    model_mouth->renderModel();

	world->finishRender ();

	glFlush();
}

void init(){

	world = new World ();
	world->setBgColor (0.0, 255.0, 0.0, 0.0);
	world->setSize (WINDOW_W, WINDOW_H);
	world->init ();

	camera = new Camera ();
	camera->setEye (0.0f, 3.0f, 60.0f);
	
	world->setCamera (camera);

    light = new Light();
    light->setPosition(pos);
    world->setLight(light);
/*
	model = new ModelAM ();
	model->loadModel ("/usr/local/share/mobile3d/model_am/quad.am");
*/
/*
	model_body = new ModelAM ();
	model_body->loadModel ("/usr/local/share/mobile3d/mii/male_body_1.am");
*/	
/*
    model_head = new ModelAM ();
	model_head->loadModel ("/usr/local/share/mobile3d/mii/male_head_changfang.am");
*/

    model_hair = new ModelAM ();
	model_hair->loadModel ("/usr/local/share/mobile3d/mii/male_hair_01.am");


    model_eyebrow_l = new ModelAM ();
	model_eyebrow_l->loadModel ("/usr/local/share/mobile3d/mii/male_eyebrow_01_l.am");

    model_eyebrow_r = new ModelAM ();
	model_eyebrow_r->loadModel ("/usr/local/share/mobile3d/mii/male_eyebrow_01_r.am");


    model_eye_l = new ModelAM ();
	model_eye_l->loadModel ("/usr/local/share/mobile3d/mii/male_eye_02_l.am");

    model_eye_r = new ModelAM ();
	model_eye_r->loadModel ("/usr/local/share/mobile3d/mii/male_eye_02_r.am");

    model_nose = new ModelAM ();
	model_nose->loadModel ("/usr/local/share/mobile3d/mii/male_nose_01.am");

    model_mouth = new ModelAM ();
	model_mouth->loadModel ("/usr/local/share/mobile3d/mii/male_mouth_03.am");


} 

void keyboard(unsigned char key, int x, int y){ 
	switch(key) 
	{
/*
		case 'f':
			printf ("f is pressed.\n");
            if (eyebrow_l_id < eyebrow_l_num - 1)
                eyebrow_l_id++;
            else
                eyebrow_l_id = 0;

            if (eyebrow_r_id < eyebrow_r_num - 1)
                eyebrow_r_id++;
            else
                eyebrow_r_id = 0;

			printf ("eyebrow_l_id = %d.\n", eyebrow_l_id);

            updateMiiEyebrows ();

			break; 
		case 'g':
            if (eye_l_id < eye_l_num - 1)
                eye_l_id++;
            else
                eye_l_id = 0;

            if (eye_r_id < eye_r_num - 1)
                eye_r_id++;
            else
                eye_r_id = 0;


            updateMiiEyes ();

			break; 
		case 'h':
            if (nose_id < nose_num - 1)
                nose_id++;
            else
                nose_id = 0;

            updateMiiNose ();

			break; 
		case 'j':
            if (mouth_id < mouth_num - 1)
                mouth_id++;
            else
                mouth_id = 0;

            updateMiiMouth ();

			break; 
*/
		case 'q': 
		case 'Q': 
		case 27: 
			exit(0); 
			break;
  	}
}

void processMouse(int button, int state, int x, int y) {
/*
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
*/
}

void processMouseActiveMotion(int x, int y) {
/*
	printf ("Mouse is moving. \n");
	angle_y = angle_y + (x - startx);
	angle_x = angle_x + (y - starty);
	startx = x;
	starty = y;
	glutPostRedisplay();
*/
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

    FREEANDNULL (model_body);
    FREEANDNULL (model_head);
    FREEANDNULL (model_hair);
    FREEANDNULL (model_eyebrow_l);
    FREEANDNULL (model_eyebrow_r);
    FREEANDNULL (model_eye_l);
    FREEANDNULL (model_eye_r);
    FREEANDNULL (model_nose);
    FREEANDNULL (model_mouth);


  	return 0;
}

#ifdef __cplusplus
}
#endif

