
#include <sys/time.h>

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
#include <mobile3d/imageBMP.h>
#include "data.h"


#define WINDOW_W    500
#define WINDOW_H    400

#define MESH_NUM 1

using namespace M3D;

World *world = NULL;
Camera *camera = NULL;
Model *model = NULL;
ImageBMP *image = NULL;
ImageTGA *imageFloor = NULL;


Model *model1 = NULL;
Model *model2 = NULL;
Model *model3 = NULL;
Model *model4 = NULL;
Model *model5 = NULL;
Model *model6 = NULL;
Model *model7 = NULL;

Model *model_floor = NULL;

float angle = 0.0;


static long int start_time = 0;
static struct timeval timeNow;

static long int duration = 1000; //ms
static long int elapse_time = 0;

#define CLOCK(v_time) v_time.tv_sec * 1000 + v_time.tv_usec / 1000

static bool enable_animation = false;

static float menu_x = 0.0f;
static float menu_y = 0.0f;
static float menu_z = 0.0f;



void display(){
 
	world->prepareRender ();

	//draw floor
	model_floor->renderModel ();

	if(enable_animation) { 
		
    	gettimeofday(&timeNow, NULL);
		elapse_time = CLOCK(timeNow) - start_time;
		if (elapse_time < duration) {
			menu_z += 0.1f;
			printf ("elapse %ld ms, duration = %ld.\n", elapse_time, duration);
		}
	} //end of enable_animation


	
	//Face 0
	if(enable_animation && angle == 0.0) { 
		model->setPosition (0.0f, 0.0f, menu_z);
	}
	model->setRotate (0.0, angle, 0.0);
	model->renderModel ();

	//Face 1
	if(enable_animation && angle == 45.0) { 
		model1->setPosition (0.0f, 0.0f, menu_z);
	}
	model1->setRotate (0.0, angle, 0.0);
	model1->renderModel ();

	//Face2
	model2->setRotate (0.0, angle, 0.0);
	model2->renderModel ();

	model3->setRotate (0.0, angle, 0.0);
	model3->renderModel ();

	model4->setRotate (0.0, angle, 0.0);
	model4->renderModel ();

	model5->setRotate (0.0, angle, 0.0);
	model5->renderModel ();


	model6->setRotate (0.0, angle, 0.0);
	model6->renderModel ();

	model7->setRotate (0.0, angle, 0.0);
	model7->renderModel ();



	
	//Face 0
	if(enable_animation && angle == 0.0) { 
		model->setPosition (0.0f, 0.0f, menu_z);
	}
	model->setRotate (0.0, angle, 0.0);
	model->renderModel ();



	//Face 1
	if(enable_animation && angle == 45.0) { 
		model1->setPosition (0.0f, 0.0f, menu_z);
	}
	model1->setRotate (0.0, angle, 0.0);
	model1->renderModel ();

	//Face2
	model2->setRotate (0.0, angle, 0.0);
	model2->renderModel ();




	//draw flection	
	glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
	model->setPosition (0.0, -4.1, 0.0);
	model->enableBlend (true, 0);
	model->setBlendFunc (GL_SRC_ALPHA, GL_ONE, 0);
	model->renderModel ();
	model->enableBlend (false, 0);
	model->setPosition (0.0, 0.0, 0.0);

	
	glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
	model1->setPosition (0.0, -4.1, 0.0);
	model1->enableBlend (true, 0);
	model1->setBlendFunc (GL_SRC_ALPHA, GL_ONE, 0);
	model1->renderModel ();
	model1->enableBlend (false, 0);
	model1->setPosition (0.0, 0.0, 0.0);

	glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
	model2->setPosition (0.0, -4.1, 0.0);
	model2->enableBlend (true, 0);
	model2->setBlendFunc (GL_SRC_ALPHA, GL_ONE, 0);
	model2->renderModel ();
	model2->enableBlend (false, 0);
	model2->setPosition (0.0, 0.0, 0.0);

	glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
	model3->setPosition (0.0, -4.1, 0.0);
	model3->enableBlend (true, 0);
	model3->setBlendFunc (GL_SRC_ALPHA, GL_ONE, 0);
	model3->renderModel ();
	model3->enableBlend (false, 0);
	model3->setPosition (0.0, 0.0, 0.0);

	glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
	model4->setPosition (0.0, -4.1, 0.0);
	model4->enableBlend (true, 0);
	model4->setBlendFunc (GL_SRC_ALPHA, GL_ONE, 0);
	model4->renderModel ();
	model4->enableBlend (false, 0);
	model4->setPosition (0.0, 0.0, 0.0);


	glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
	model5->setPosition (0.0, -4.1, 0.0);
	model5->enableBlend (true, 0);
	model5->setBlendFunc (GL_SRC_ALPHA, GL_ONE, 0);
	model5->renderModel ();
	model5->enableBlend (false, 0);
	model5->setPosition (0.0, 0.0, 0.0);

	glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
	model6->setPosition (0.0, -4.1, 0.0);
	model6->enableBlend (true, 0);
	model6->setBlendFunc (GL_SRC_ALPHA, GL_ONE, 0);
	model6->renderModel ();
	model6->enableBlend (false, 0);
	model6->setPosition (0.0, 0.0, 0.0);

	glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
	model7->setPosition (0.0, -4.1, 0.0);
	model7->enableBlend (true, 0);
	model7->setBlendFunc (GL_SRC_ALPHA, GL_ONE, 0);
	model7->renderModel ();
	model7->enableBlend (false, 0);
	model7->setPosition (0.0, 0.0, 0.0);

	world->finishRender ();

	glFlush();
}

void init(){

	printf ("%s.\n", glGetString(GL_EXTENSIONS));

	world = new World ();
	world->setSize (WINDOW_W, WINDOW_H);
	world->init ();

	camera = new Camera ();
	camera->setEye (0.0f, 2.0f, 15.0f);
	
	world->setCamera (camera);

	image = new ImageBMP ();
	Texture *texture = image->loadTexture ("/usr/local/share/mobile3d/mmi/menu.bmp");


	model = new Model ();
	model->setMeshCount (MESH_NUM);

    model->setVertices(afVertices, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model->setTriangleNums(TRIANGLE_NUM, 0);
	if (texture != NULL)
		model->setTextureId (texture->textureId, 0);


	model1 = new Model ();
	model1->setMeshCount (MESH_NUM);

    model1->setVertices(afVertices1, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model1->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model1->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model1->setTriangleNums(TRIANGLE_NUM, 0);
	if (texture != NULL)
		model1->setTextureId (texture->textureId, 0);


	model2 = new Model ();
	model2->setMeshCount (MESH_NUM);

    model2->setVertices(afVertices2, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model2->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model2->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model2->setTriangleNums(TRIANGLE_NUM, 0);
	if (texture != NULL)
		model2->setTextureId (texture->textureId, 0);


	model3 = new Model ();
	model3->setMeshCount (MESH_NUM);

    model3->setVertices(afVertices3, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model3->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model3->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model3->setTriangleNums(TRIANGLE_NUM, 0);
	if (texture != NULL)
		model3->setTextureId (texture->textureId, 0);


	model4 = new Model ();
	model4->setMeshCount (MESH_NUM);

    model4->setVertices(afVertices4, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model4->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model4->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model4->setTriangleNums(TRIANGLE_NUM, 0);
	if (texture != NULL)
		model4->setTextureId (texture->textureId, 0);


	model5 = new Model ();
	model5->setMeshCount (MESH_NUM);

    model5->setVertices(afVertices5, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model5->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model5->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model5->setTriangleNums(TRIANGLE_NUM, 0);
	if (texture != NULL)
		model5->setTextureId (texture->textureId, 0);

	model6 = new Model ();
	model6->setMeshCount (MESH_NUM);

    model6->setVertices(afVertices6, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model6->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model6->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model6->setTriangleNums(TRIANGLE_NUM, 0);
	if (texture != NULL)
		model6->setTextureId (texture->textureId, 0);


	model7 = new Model ();
	model7->setMeshCount (MESH_NUM);

    model7->setVertices(afVertices7, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model7->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model7->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model7->setTriangleNums(TRIANGLE_NUM, 0);
	if (texture != NULL)
		model7->setTextureId (texture->textureId, 0);


	//floor
	imageFloor = new ImageTGA ();
	Texture *textureFloor = imageFloor->loadTexture ("/usr/local/share/mobile3d/mmi/floor.tga");

	model_floor = new Model ();
	model_floor->setMeshCount (MESH_NUM);

    model_floor->setVertices(afVerticesFloor, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
   	model_floor->setIndices(afVertIndices, TRIANGLE_NUM * 3 * sizeof(GLshort), 0);
	model_floor->setUvs(afTexCoord, VERTEX_NUM * 2 * sizeof (GLfloat), 0);
    model_floor->setTriangleNums(TRIANGLE_NUM, 0);
	if (texture != NULL)
		model_floor->setTextureId (textureFloor->textureId, 0);


	//model->setScale (0.5f, 0.5f, 0.5f);



}

void keyboard(unsigned char key, int x, int y){
  switch(key) {
    case 'q': case 'Q': case 27:
      exit(0);
      break;

    case 'r': case 'R': case 28:
		angle += 22.5;
      	if(angle >= 360)
			angle -= 360;
		printf ("angle = %f.\n", angle);
			
      break;

    case 's': case 'S': case 29:
		if (enable_animation) {
			enable_animation = false;

			menu_x = 0.0f;
			menu_y = 0.0f;
			menu_z = 0.0f;

			//model_oil->setPosition (0.0f, 0.0f, 0.0f);


		}
		else {
			enable_animation = true;
    		gettimeofday(&timeNow, NULL);
			start_time = CLOCK(timeNow);
		}

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


