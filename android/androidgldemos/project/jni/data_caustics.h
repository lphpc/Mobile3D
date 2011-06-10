
#ifndef _DATA_CAUSTICS_H
#define _DATA_CAUSTICS_H

#define VERTEX_NUM_CAUSTICS 4
#define TRIANGLE_NUM_CAUSTICS 2




GLfloat afVerticesCaustics[]= {
	-1.4339, -1.4339, 1.83801,
	1.4339, -1.4339, 1.83801,
	-1.4339, 1.4339, 1.83801,
	1.4339, 1.4339, 1.83801,
};

GLfloat afTexCoordCaustics[] = {
	0.0, 0.0,
	1.0, 0.0,
	0.0, 1.0,
	1.0, 1.0,
};

GLshort afVertIndicesCaustics[] = {
	0, 1, 3,
	3, 2, 0,
};

GLfloat afNormalsCaustics[] = {
	0, 0, 1, 0, 0, 1, 0, 0, 1,
	0, 0, 1, 0, 0, 1, 0, 0, 1,
};


#endif





