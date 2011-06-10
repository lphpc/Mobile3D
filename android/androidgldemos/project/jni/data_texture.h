
#ifndef _DATA_TEXTURE_H
#define _DATA_TEXTURE_H


#define VERTEX_NUM_TEXTURE 4
#define TRIANGLE_NUM_TEXTURE 2




GLfloat afVerticesTexture[]= {
	-1.4339, -1.4339, 1.83801,
	1.4339, -1.4339, 1.83801,
	-1.4339, 1.4339, 1.83801,
	1.4339, 1.4339, 1.83801,
};

GLfloat afTexCoordTexture[] = {
	0.0, 0.0,
	1.0, 0.0,
	0.0, 1.0,
	1.0, 1.0,
};

GLshort afVertIndicesTexture[] = {
	0, 1, 3,
	3, 2, 0,
};

GLfloat afNormalsTexture[] = {
	0, 0, 1, 0, 0, 1, 0, 0, 1,
	0, 0, 1, 0, 0, 1, 0, 0, 1,
};


#endif





