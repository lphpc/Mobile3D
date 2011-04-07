
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <mobile3d/m3d.h>
#include <mobile3d/world.h>
#include <mobile3d/camera.h>
#include <mobile3d/model.h>
#include <mobile3d/M3DRenderer.h>
#include <mobile3d/M3DMeshData.h>
#include "data.h"


#define WINDOW_W    500
#define WINDOW_H    500

using namespace M3D;

World *world = NULL;
Camera *camera = NULL;
//Model *model = NULL;

Model *models[2];
int modelNum = 2;

static int startx = 0, starty = 0;
static GLfloat angle_x = 0;   /* in degrees */
static GLfloat angle_y = 0;   /* in degrees */


int vertexNum = 6;
int triangleNum = 8;


Model *createModel (GLfloat* vert, int size, float height)
{
	
	Model *model = NULL;
	GLfloat vert_tmp [18];

	int j = 0;
	for (int i = 0; i < size; i+=2) {
		vert_tmp [j++] = vert[i];
		vert_tmp [j++] = vert[i+1];
		vert_tmp [j++] = 0.0f;
		
	}

	for (int i = 0; i < size; i+=2) {
		vert_tmp [j++] = vert[i];
		vert_tmp [j++] = vert[i+1];
		vert_tmp [j++] = height;
	}
	
	for (int i = 0; i < 18; i ++)
		printf ("vert_tmp[%d] = %f.\n", i, vert_tmp[i]);

	model = new Model ();
	model->setMeshCount (MESH_NUM);

    model->setVertices(vert_tmp, vertexNum * 3 * sizeof(GLfloat), 0);
	model->setIndices (indices, sizeof(GLshort) * 3 * triangleNum , 0);	
    model->setTriangleNums(triangleNum, 0);

	return model;

}


void display(){
/*
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
*/
/*
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices0);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);
	glDrawArrays(GL_TRIANGLES, 0, 1 * 3);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
*/
/*
	glBegin(GL_TRIANGLES);						// Drawing Using Triangles
		glVertex3f(-1.0f, -1.0f, 0.0f);				// Top
		glVertex3f(1.0f,-1.0f, 0.0f);				// Bottom Left
		glVertex3f( 0.0f,1.0f, 0.0f);				// Bottom Right
	glEnd();							// Finished Drawing The Triangle
*/
 
	world->prepareRender ();

	//model->setRotate (angle_x, angle_y, 0.0);
	models[0]->setRotate (angle_x, angle_y, 0.0);
	models[1]->setRotate (angle_x, angle_y, 0.0);

  	glPolygonMode(GL_FRONT, GL_LINE);
  	glPolygonMode(GL_BACK, GL_LINE);

	models[0]->renderModel ();
	models[1]->renderModel ();
	//model->renderModel ();

  	glPolygonMode(GL_FRONT, GL_FILL);
  	glPolygonMode(GL_BACK, GL_FILL);

	world->finishRender ();

	glFlush();
}

void init(){

	world = new World ();
	world->setSize (WINDOW_W, WINDOW_H);
	world->init ();

	camera = new Camera ();
	camera->setEye (0.0f, 5.0f, 5.0f);

	world->setCamera (camera);


	models[0] = createModel (vertices1, 6, 1.0);
	models[1] = createModel (vertices2, 6, 2.0);


/*
	model = createModel (vertices1, 6, 1.0f);
*/
/*	
	model = new Model ();
	model->setMeshCount (MESH_NUM);

    model->setVertices(vertices, vertexNum * 3 * sizeof(GLfloat), 0);
	model->setIndices (indices, sizeof(GLshort) * 3 * triangleNum , 0);	
    model->setTriangleNums(triangleNum, 0);
*/	
}

void keyboard(unsigned char key, int x, int y){
  switch(key) {
    case 'q': case 'Q': case 27:
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
	FREEANDNULL (models[0]);
	FREEANDNULL (models[1]);
	//FREEANDNULL (model);
  	return 0;
}


