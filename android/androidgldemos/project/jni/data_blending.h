
#ifndef _DATA_TEXTURE_H
#define _DATA_TEXTURE_H


#define VERTEX_NUM_BLENDING 4
#define TRIANGLE_NUM_BLENDING 2




GLfloat afVerticesBlending[]= {
	-1.4339, -1.4339, 1.83801,
	1.4339, -1.4339, 1.83801,
	-1.4339, 1.4339, 1.83801,
	1.4339, 1.4339, 1.83801,
};

GLfloat afTexCoordBlending[] = {
	0.0, 0.0,
	1.0, 0.0,
	0.0, 1.0,
	1.0, 1.0,
};

GLshort afVertIndicesBlending[] = {
	0, 1, 3,
	3, 2, 0,
};

GLfloat afNormalsBlending[] = {
	0, 0, 1, 0, 0, 1, 0, 0, 1,
	0, 0, 1, 0, 0, 1, 0, 0, 1,
};


#endif





