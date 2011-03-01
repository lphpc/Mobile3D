
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

#define USEINDEX 1
#define USEVBO 1
#define USESOFTVBO 1

#define WINDOW_W    500
#define WINDOW_H    500

using namespace M3D;

World *world = NULL;
Camera *camera = NULL;
Model *model = NULL;


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

	model->renderModel ();

	world->finishRender ();

	glFlush();
}

void init(){

	world = new World ();
	world->setSize (WINDOW_W, WINDOW_H);
	world->init ();

	camera = new Camera ();
	camera->setEye (0.0f, 0.0f, 5.0f);
	
	world->setCamera (camera);

	model = new Model ();
	model->setMeshCount (MESH_NUM);

#ifdef USESOFTVBO

	M3DMeshData *data = new M3DMeshData ();
	data->setTriangleNums (1);	
	data->setVertices (vertices0, sizeof(GLfloat) * 3, VERTEX_NUM);	
	data->setIndices (indices0, sizeof(GLshort) * 3, 1 * 3);	
	data->setColors (colors, VERTEX_NUM * 4 * sizeof(GLubyte));	
	model->loadMesh (data, 0);
	delete data;

#else

#ifdef USEVBO
    //init second triangle
	size_t vertexSizeInBytes = VERTEX_NUM * 3 * sizeof(GLfloat) + 1 * 3 * sizeof(GLshort);
	//size_t vertexSizeInBytes = VERTEX_NUM * 3 * sizeof(GLfloat) + VERTEX_NUM * 4 * sizeof(GLubyte);
	size_t indexSizeInBytes = 1 * 3 * sizeof(GLshort);
	model->createVBO (vertexSizeInBytes, indexSizeInBytes, 0);
#endif

    model->setVertices(vertices0, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
#ifdef USEINDEX
    model->setIndices(indices0, 1 * 3 * sizeof(GLshort), 0);
#endif
    model->setColors(colors, VERTEX_NUM * 4 * sizeof(GLubyte), 0);
    model->setTriangleNums(1, 0);

#endif  //end of SOFTVBO
	
}

void keyboard(unsigned char key, int x, int y){
  switch(key) {
    case 'q': case 'Q': case 27:
#ifdef USEVBO
		model->destroyVBO ();
#endif
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


