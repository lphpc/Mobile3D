
#define VERTEX_NUM 4
#define TRIANGLE_NUM 2




GLfloat afVertices[]= {
	-4.0, -1.0, -1.5,
	-1.6, -1.0, -1.5,
	-4.0, 1.0, -1.5,
	-1.6, 1.0, -1.5,
};



GLfloat afVerticesR[]= {
	1.6, -1.0, -1.5,
	4.0, -1.0, -1.5,
	1.6, 1.0, -1.5,
	4.0, 1.0, -1.5,
};

GLfloat afVerticesF[]= {


   -4.0, -2.0, -10.0,
	4.0, -2.0, -10.0,
   -4.0, 2.0, -10.0,
	4.0, 2.0, -10.0,


};

GLfloat afVerticesOil[]= {


   -0.4, -0.5, -1.0,
	0.4, -0.5, -1.0,
   -0.4, 0.5, -1.0,
	0.4, 0.5, -1.0,


};


/*
GLfloat afVertices[]= {
	-1.2, -1.0, 0.0,
	1.2, -1.0, 0.0,
	-1.2, 1.0, 0.0,
	1.2, 1.0, 0.0,
};
*/

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
	-0.03, -0.1, 1.83801,
	0.0, -0.6, 1.83801,
	0.0, 0.0, 1.83801,
	0.03, -0.1, 1.83801,
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





