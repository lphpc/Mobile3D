
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


extern M3D::am_model_t **bodies;
extern int body_num;
int body_id = 0;

extern M3D::am_model_t **heads;
extern int head_num;
int head_id = 0;

extern M3D::am_model_t **hair;
extern int hair_num;
int hair_id = 0;

extern M3D::am_model_t **eyebrows_l;
extern int eyebrow_l_num;
int eyebrow_l_id = 0;

extern M3D::am_model_t **eyebrows_r;
extern int eyebrow_r_num;
int eyebrow_r_id = 0;

extern M3D::am_model_t **eyes_l;
extern int eye_l_num;
int eye_l_id = 0;

extern M3D::am_model_t **eyes_r;
extern int eye_r_num;
int eye_r_id = 0;

extern M3D::am_model_t **noses;
extern int nose_num;
int nose_id = 0;

extern M3D::am_model_t **mouths;
extern int mouth_num;
int mouth_id = 0;

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

extern bool loadAllMeshes ();
extern void destroyAllMeshes ();
extern void dumpBodies ();


void createDefaultMii ()
{

    model_body = new M3D::ModelAM ();
    model_body->loadModel (bodies[body_id]);

    model_head = new M3D::ModelAM ();
    model_head->loadModel (heads[head_id]);

    model_hair = new M3D::ModelAM ();
    model_hair->loadModel (hair[hair_id]);

    model_eyebrow_l = new M3D::ModelAM ();
    model_eyebrow_l->loadModel (eyebrows_l[eyebrow_l_id]);

    model_eyebrow_r = new M3D::ModelAM ();
    model_eyebrow_r->loadModel (eyebrows_r[eyebrow_r_id]);

    model_eye_l = new M3D::ModelAM ();
    model_eye_l->loadModel (eyes_l[eye_l_id]);

    model_eye_r = new M3D::ModelAM ();
    model_eye_r->loadModel (eyes_r[eye_r_id]);

    model_nose = new M3D::ModelAM ();
    model_nose->loadModel (noses[nose_id]);

    model_mouth = new M3D::ModelAM ();
    model_mouth->loadModel (mouths[mouth_id]);

    printf ("A person is created.\n");


    return;
}


void updateMiiEyebrows ()
{
    if (model_eyebrow_l == NULL)
        model_eyebrow_l = new ModelAM ();

    model_eyebrow_l->updateModel (eyebrows_l[eyebrow_l_id]);


    if (model_eyebrow_r == NULL)
        model_eyebrow_r = new ModelAM ();

    model_eyebrow_r->updateModel (eyebrows_r[eyebrow_r_id]);

}

void updateMiiEyes ()
{
    if (model_eye_l == NULL)
        model_eye_l = new ModelAM ();

    model_eye_l->updateModel (eyes_l[eye_l_id]);


    if (model_eye_r == NULL)
        model_eye_r = new ModelAM ();

    model_eye_r->updateModel (eyes_r[eye_r_id]);

}


void updateMiiNose ()
{
    if (model_nose == NULL)
        model_nose = new ModelAM ();

    model_nose->updateModel (noses[nose_id]);
}


void updateMiiMouth ()
{
    if (model_mouth == NULL)
        model_mouth = new ModelAM ();

    model_mouth->updateModel (mouths[mouth_id]);
}




void display(){

	world->prepareRender ();

	//model->renderModel ();

    model_body->renderModel();
    model_head->renderModel();
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
	model->loadModel ("res/male_hair_01.am");
*/
/*
	model_body = new ModelAM ();
	model_body->loadModel ("res/male_body_1.am");
	
    model_head = new ModelAM ();
	model_head->loadModel ("res/male_head_changfang.am");

    model_hair = new ModelAM ();
	model_hair->loadModel ("res/male_hair_01.am");

    model_eyebrow_l = new ModelAM ();
	model_eyebrow_l->loadModel ("res/male_eyebrow_01_l.am");

    model_eyebrow_r = new ModelAM ();
	model_eyebrow_r->loadModel ("res/male_eyebrow_01_r.am");

    model_eye_l = new ModelAM ();
	model_eye_l->loadModel ("res/male_eye_01_l.am");

    model_eye_r = new ModelAM ();
	model_eye_r->loadModel ("res/male_eye_01_r.am");

    model_nose = new ModelAM ();
	model_nose->loadModel ("res/male_nose_01.am");

    model_mouth = new ModelAM ();
	model_mouth->loadModel ("res/male_mouth_01.am");
*/

    loadAllMeshes ();
    createDefaultMii ();
	//dumpBodies ();


} 

void keyboard(unsigned char key, int x, int y){ 
	switch(key) 
	{
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

    destroyAllMeshes ();

  	return 0;
}

#ifdef __cplusplus
}
#endif

