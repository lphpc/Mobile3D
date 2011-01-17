
#define VERTEX_NUM 4
#define TRIANGLE_NUM 2




GLfloat afVertices[]= {
	-1.4339, -1.4339, 1.83801,
	1.4339, -1.4339, 1.83801,
	-1.4339, 1.4339, 1.83801,
	1.4339, 1.4339, 1.83801,
};

GLfloat afTexCoord[] = {
	0.0, 0.0,
	1.0, 0.0,
	0.0, 1.0,
	1.0, 1.0,
};

GLshort afVertIndices[] = {
	0, 1, 3,
	3, 2, 0,
};

GLfloat afNormals[] = {
	0, 0, 1, 0, 0, 1, 0, 0, 1,
	0, 0, 1, 0, 0, 1, 0, 0, 1,
};








