
#ifndef _DATA_H
#define _DATA_H

#define MESH_NUM 2
#define VERTEX_NUM 3


//triangle data
GLfloat vertices0[9] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f
};

GLshort indices0[] = {
	0, 1, 2,
};

GLfloat vertices1[9] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f
};

GLshort indices1[] = {
	0, 1, 2,
};

GLubyte colors[12] = {
    255, 0, 0, 0,
    0, 255, 0, 0,
    0, 0, 255 ,0
};

#endif
