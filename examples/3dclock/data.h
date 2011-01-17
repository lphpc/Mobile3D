
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


#define VERTEX_NUM_POINTER 4
#define TRIANGLE_NUM_POINTER 2




GLfloat afVerticesPointer[]= {
	-0.05, 0.2, 1.83801,
	0.0, 0.0, 1.83801,
	0.0, 1.0, 1.83801,
	0.05, 0.2, 1.83801,
};

GLfloat afTexCoordPointer[] = {
	0.0, 0.0,
	1.0, 0.0,
	0.0, 1.0,
	1.0, 1.1,
};

GLshort afVertIndicesPointer[] = {
	0, 1, 3,
	3, 2, 0,
};

GLfloat afNormalsPointer[] = {
	0, 0, 1, 0, 0, 1, 0, 0, 1,
	0, 0, 1, 0, 0, 1, 0, 0, 1,
};



#define VERTEX_NUM_POINTER_SMALL 4
#define TRIANGLE_NUM_POINTER_SMALL 2




GLfloat afVerticesPointerSmall[]= {
	-0.03, -0.1, 1.83801,
	0.0, -0.6, 1.83801,
	0.0, 0.0, 1.83801,
	0.03, -0.1, 1.83801,
};

/*
GLfloat afVerticesPointerSmall[]= {
	-0.19, -0.6, 1.83801,
	-0.16, -1.1, 1.83801,
	-0.16, -0.5, 1.83801,
	-0.13, -0.6, 1.83801,
};
*/

GLfloat afTexCoordPointerSmall[] = {
	0.0, 0.0,
	1.0, 0.0,
	0.0, 1.0,
	1.0, 1.1,
};

GLshort afVertIndicesPointerSmall[] = {
	0, 1, 3,
	3, 2, 0,
};

GLfloat afNormalsPointerSmall[] = {
	0, 0, 1, 0, 0, 1, 0, 0, 1,
	0, 0, 1, 0, 0, 1, 0, 0, 1,
};





