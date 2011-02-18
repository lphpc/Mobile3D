

#include "M3DQuad.h"


M3D_BEGIN_NAMESPACE


M3DQuad::M3DQuad()
{
	meshCount = 1;
	triangleCount = 2;
	vertexCount = 4;
	uvCount = vertexCount;
	indexCount = triangleCount;
}

M3DQuad::~M3DQuad() {

}


void M3DQuad::draw () 
{

	model.renderModel ();

}

/*
 * image's width and height must base on 2
 */
void M3DQuad::create (float x, float y, float width, float height, const char* fileName)
{
	float *vertices = NULL;
	float *uvs = NULL;
	short *indices = NULL;

	model.setMeshCount (meshCount);
	model.setTriangleNums(triangleCount, 0);

    vertices = (float*)malloc (vertexCount * 3 * sizeof (float));
    if (!vertices) {
    	return;
    }

	// (x, y) in world coordinate
	// v2 ------------------ v3
    //    |                |
    //    |                |
    //    |                |
    //    |                |
    //    |                |
    // v0 ------------------ v1
	//start from left bottom , counterclockwise
	vertices [0] = x;
	vertices [1] = y - height;
	vertices [2] = 0.0;
	vertices [3] = x + width;
	vertices [4] = y - height;
	vertices [5] = 0.0;
	vertices [6] = x;
	vertices [7] = y;
	vertices [8] = 0.0;
	vertices [9] = x + width;
	vertices [10] = y;
	vertices [11] = 0.0;

	
    model.setVertices (vertices, vertexCount * 3 * sizeof (float), 0);
    FREEANDNULL (vertices);


    indices = (short *)malloc (triangleCount * 3 * sizeof (short));
    if (!indices) {
        return;
    }

	indices [0] = 0; 
	indices [1] = 1; 
	indices [2] = 3; 
	indices [3] = 3; 
	indices [4] = 2; 
	indices [5] = 0;

    model.setIndices (indices, triangleCount * 3 * sizeof (short), 0);
    FREEANDNULL (indices);


 	// uv(0.0, 1.0)          uv(1.0, 1.0)
	// v2 ------------------ v3
    //    |                |
    //    |                |
    //    |                |
    //    |                |
    //    |                |
    // v0 ------------------ v1
    // uv(0.0, 0.0)         uv(1.0, 0.0)
	//start from left bottom 

	if (fileName) {
   		uvs = (float*)malloc (uvCount * 2 * sizeof (float));
   		if (!uvs) {
   			return;
   		}
		uvs [0] = 0.0;
		uvs [1] = 0.0;
		uvs [2] = 1.0;
		uvs [3] = 0.0;
		uvs [4] = 0.0;
		uvs [5] = 1.0;
		uvs [6] = 1.0;
		uvs [7] = 1.0;

   		model.setUvs(uvs, uvCount * 2 * sizeof (float), 0);
   		FREEANDNULL (uvs);


		//new/delete compile error in android
		ImageTGA *image = (ImageTGA*) malloc(sizeof(ImageTGA));
		//ImageTGA *image = new ImageTGA ();
		Texture *texture = image->loadTexture (fileName);
    	if (texture != NULL)
        	model.setTextureId (texture->textureId, 0);

		FREEANDNULL (texture);
		FREEANDNULL (image);

	}


    return;
}

void M3DQuad::rotate (float x, float y, float z)
{
	model.setRotate (x, y, z);
}

void M3DQuad::translate (float x, float y, float z)
{
	model.setPosition (x, y, z);
}


M3D_END_NAMESPACE
