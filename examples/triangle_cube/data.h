
#ifndef _DATA_H
#define _DATA_H

#define MESH_NUM 1
#define VERTEX_NUM 3


//triangle data
GLfloat vertices0[9] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};

GLshort indices0[] = {
	0, 1, 2,
};

GLubyte colors[12] = {
    255, 0, 0, 0,
    0, 255, 0, 0,
    0, 0, 255 ,0
};


GLfloat vertices[18] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    0.0f, 1.0f, 1.0f

};

GLshort indices[] = {
	0, 1, 2,
	3, 4, 5,
	0, 1, 4, 
	4, 3, 0,
	1, 2, 5,
	5, 4, 1,
	2, 0, 3,
	3, 5, 2
};


//triangle data
GLfloat vertices1[6] = {
    -1.0f, -1.0f, 
    1.0f, -1.0f, 
    0.0f, 1.0f, 
};

GLfloat vertices2[6] = {
    1.0f, -1.0f, 
    1.5f, 1.0f, 
    0.0f, 1.0f, 
};



#endif
