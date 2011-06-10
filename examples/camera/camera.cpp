
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <mobile3d/m3d.h>
#include <mobile3d/world.h>
#include <mobile3d/camera.h>
#include <mobile3d/model.h>
#include <mobile3d/imageTGA.h>
#include "data.h"

#define WINDOW_W    500
#define WINDOW_H    500

using namespace M3D;

World *world = NULL;
Camera *camera = NULL;
Model *model_tri = NULL;
Model *model = NULL;
ImageTGA *image = NULL;


float camera_x = 0.0f;
float camera_y = 0.0f;
float camera_z = 0.0f;



typedef struct {         // vertex coordinates - 3d and texture
    GLfloat x, y, z;     // 3d coords.
    GLfloat u, v;        // texture coords.
} VERTEX;

typedef struct {         // triangle
    VERTEX vertex[3];    // 3 vertices array
} TRIANGLE;

typedef struct {         // sector of a 3d environment
    int numtriangles;    // number of triangles in the sector
    TRIANGLE* triangle;  // pointer to array of triangles.
} SECTOR;

SECTOR sector1;


void readstr(FILE *f, char *string)
{
    do {
        fgets(string, 255, f); // read the line
    } while ((string[0] == '/') || (string[0] == '\n'));
    return;
}

GLfloat *vertices = NULL;
GLfloat *uvs = NULL;

void load_model ()
{

    float x, y, z, u, v;
    int vert;
    int numtriangles;
    FILE *filein;        // file to load the world from
    char oneline[255];
    filein = fopen("/usr/local/share/mobile3d/camera/world.txt", "rt");

    readstr(filein, oneline);
    sscanf(oneline, "NUMPOLLIES %d\n", &numtriangles);

/*
    sector1.numtriangles = numtriangles;
    sector1.triangle = (TRIANGLE *) malloc(sizeof(TRIANGLE)*numtriangles);

    for (int loop = 0; loop < numtriangles; loop++) {
        for (vert = 0; vert < 3; vert++) {
            readstr(filein,oneline);
            sscanf(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);
            sector1.triangle[loop].vertex[vert].x = x;
            sector1.triangle[loop].vertex[vert].y = y;
            sector1.triangle[loop].vertex[vert].z = z;
            sector1.triangle[loop].vertex[vert].u = u;
            sector1.triangle[loop].vertex[vert].v = v;
        }
    }
*/

    vertices = (GLfloat*) malloc (sizeof (GLfloat) * numtriangles * 3 * 3);
    uvs = (GLfloat*) malloc (sizeof (GLfloat) * numtriangles * 3 * 2);


    int i = 0;
    int j = 0;
    for (int loop = 0; loop < numtriangles; loop++) {
        for (vert = 0; vert < 3; vert++) {
            readstr(filein,oneline);
            sscanf(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);
	    printf ("%f, %f, %f, %f, %f\n", x, y, z, u, v);
	    vertices[i++] = x;
	    vertices[i++] = y;
	    vertices[i++] = z;
	    uvs[j++] = u;
	    uvs[j++] = v;

        }
    }

    printf ("i = %d, j  = %d.\n",i, j);

    model = new Model ();
    model->setMeshCount (MESH_NUM);

    image = new ImageTGA ();
    Texture *texture = image->loadTexture ("/usr/local/share/mobile3d/camera/mud.tga");

    //init second triangle
    model->setVertices(vertices, numtriangles * 3 * 3 * sizeof(GLfloat), 0);
    model->setUvs(uvs, numtriangles * 3 * 2 * sizeof(GLfloat), 0);
    //model->setColors(colors, VERTEX_NUM * 4 * sizeof(GLubyte), 0);
    model->setTriangleNums(numtriangles, 0);

    if (texture != NULL)
	model->setTextureId (texture->textureId, 0);



    fclose(filein);

    free (vertices);
    free (uvs);


    return;

}


void display(){
 
	world->prepareRender ();
	model->renderModel ();
	//model_tri->renderModel ();
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

	model_tri = new Model ();
	model_tri->setMeshCount (MESH_NUM);

    //init second triangle
    model_tri->setVertices(vertices0, VERTEX_NUM * 3 * sizeof(GLfloat), 0);
    model_tri->setColors(colors, VERTEX_NUM * 4 * sizeof(GLubyte), 0);
    model_tri->setTriangleNums(1, 0);

	load_model ();
	
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


    case 'a': case 'A':
	camera->yaw (1.0f);
        glutPostRedisplay();

      break;

    case 'd': case 'D':
	camera->yaw (-1.0f);
        glutPostRedisplay();

      break;



    case 'w': case 'W': 

	camera->move (0.0f, 0.0f, -0.1f);
        glutPostRedisplay();

      break;

    case 's': case 'S': 
	camera->move (0.0f, 0.0f, 0.1f);
        glutPostRedisplay();


    case 'j': case 'J': 

	camera->moveRelative (0.0f, 0.0f, -0.1f);
        glutPostRedisplay();

      break;

    case 'l': case 'L': 
	camera->moveRelative (0.0f, 0.0f, 0.1f);
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
	FREEANDNULL (model_tri);
  	return 0;
}


