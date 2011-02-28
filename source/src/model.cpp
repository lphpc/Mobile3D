
#include "model.h"
#include "log.h"

M3D_BEGIN_NAMESPACE

Mesh::Mesh() {

	initMemberVars ();
}

void Mesh::initMemberVars () {
	m_vertices = NULL;
    m_normals = NULL;
    m_uvs = NULL;
    m_colors = NULL;
    m_indices = NULL;
    m_position = NULL;
    m_rotate = NULL;
    m_scale = NULL;
    m_textureId = -1;
    m_triangleNums = 0;
    m_enabled = GL_FALSE;
    m_materialAmbient = NULL;
    m_materialDiffuse = NULL;
    m_materialSpecular = NULL;
    m_materialEmission = NULL;
    m_materialShininess = NULL;
	m_blendEnabled = false;
	m_matrix = NULL;
	m_renderPrimitivesMode = GL_TRIANGLES;

	m_hardwareVertexBuffer = NULL;
	m_hardwareIndexBuffer = NULL;

	m_positionSizeInBytes = 0;
	m_colorSizeInBytes = 0;
	m_uvSizeInBytes = 0;


}

Mesh::~Mesh() {
    FREEANDNULL(m_vertices);
    FREEANDNULL(m_normals);
    FREEANDNULL(m_uvs);
    FREEANDNULL(m_colors);
    FREEANDNULL(m_indices);
    FREEANDNULL(m_position);
    FREEANDNULL(m_rotate);
    FREEANDNULL(m_scale);
    FREEANDNULL(m_materialAmbient);
    FREEANDNULL(m_materialDiffuse);
    FREEANDNULL(m_materialSpecular);
    FREEANDNULL(m_materialEmission);
    FREEANDNULL(m_materialShininess);
    FREEANDNULL(m_matrix);
	delete (m_hardwareVertexBuffer);
	delete (m_hardwareIndexBuffer);

}

/*
 *  hardware buffer :
 *  |position data | color data/uv data |
 *  color data and uv data can not coexist.
 */
void Mesh::setVertices(GLfloat *vertices, int size) {
/*
    FREEANDNULL(m_vertices);
    m_vertices = (GLfloat *) malloc(size);
    memcpy(m_vertices, vertices, size);
*/

	///////
	//m_hardwareVertexBuffer = new M3DHardwareVertexBuffer (size, vertices, GL_STATIC_DRAW);


	//position and colors
	//int allSize = size + 3 * 4 * sizeof(GLubyte);
	//m_hardwareVertexBuffer = new M3DHardwareVertexBuffer (allSize, vertices, GL_STATIC_DRAW);


	m_positionSizeInBytes = size;
	if (m_hardwareVertexBuffer) {
		m_hardwareVertexBuffer->writeData (0, m_positionSizeInBytes, vertices, GL_STATIC_DRAW, false);
	}
	else {
    	FREEANDNULL(m_vertices);
    	m_vertices = (GLfloat *) malloc(size);
    	memcpy(m_vertices, vertices, size);
	}


    setEnabled(GL_TRUE);
}

void Mesh::setNormals(GLfloat *normals, int size) {
    FREEANDNULL(m_normals);
    m_normals = (GLfloat *) malloc(size);
    memcpy(m_normals, normals, size);
}

/*
 *  hardware buffer :
 *  |position data | color data/uv |
 *  color data and uv data can not coexist.
 */
void Mesh::setUvs(GLfloat *uvs, int size) {

	m_uvSizeInBytes = size;
	if (m_hardwareVertexBuffer) {
		m_hardwareVertexBuffer-> writeData (m_positionSizeInBytes, size, uvs, GL_STATIC_DRAW, false);
	}
	else {
    	FREEANDNULL(m_uvs);
    	m_uvs = (GLfloat *) malloc(size);
    	memcpy(m_uvs, uvs, size);
	}
}


/*
 *  hardware buffer :
 *  |position data | color data/uv data |
 *  color data and uv data can not coexist.
 */

void Mesh::setColors(GLubyte *colors, int size) {
/*
    FREEANDNULL(m_colors);
    m_colors = (GLubyte *) malloc(size);
    memcpy(m_colors, colors, size);
*/
/*
	int offset = 3 * 3 * sizeof(GLfloat);
	m_hardwareVertexBuffer->writeData (offset, size, colors, GL_STATIC_DRAW, false);
*/
	m_colorSizeInBytes = size;
	if (m_hardwareVertexBuffer)
		m_hardwareVertexBuffer->writeData (m_positionSizeInBytes, m_colorSizeInBytes, colors, GL_STATIC_DRAW, false);
	else {
    	FREEANDNULL(m_colors);
    	m_colors = (GLubyte *) malloc(size);
    	memcpy(m_colors, colors, size);

	}
}

void Mesh::setIndices(GLshort *indices, int size) {
/*
    FREEANDNULL(m_indices);
    m_indices = (GLshort *) malloc(size);
    memcpy(m_indices, indices, size);\
*/
/*
	m_hardwareIndexBuffer = new M3DHardwareIndexBuffer (size, indices, GL_STATIC_DRAW);
*/
	if (m_hardwareIndexBuffer) {
		m_hardwareIndexBuffer->writeData (0, size, indices, GL_STATIC_DRAW, false);
	}
	else {
    	FREEANDNULL(m_indices);
    	m_indices = (GLshort *) malloc(size);
    	memcpy(m_indices, indices, size);

	}
}

void Mesh::setTextureId(GLint textureId) {
    m_textureId = textureId;
}

void Mesh::setTriangleNums(GLint triangleNums) {
    m_triangleNums = triangleNums;
}

void Mesh::setEnabled(GLboolean enabled) {
    m_enabled = enabled;
}

void Mesh::setPosition(GLfloat x, GLfloat y, GLfloat z) {
    if (m_position == NULL) {
        m_position = (GLfloat *) malloc(3 * sizeof(GLfloat));
    }

    m_position[0] = x;
    m_position[1] = y;
    m_position[2] = z;
}


bool Mesh::getPosition(GLfloat *x, GLfloat *y, GLfloat *z){
	if (m_position != NULL){
		*x = m_position[0];
		*y = m_position[1];
		*z = m_position[2];
		return true;
	}

	return false;
}

void Mesh::setRotate(GLfloat x, GLfloat y, GLfloat z) {
    if (m_rotate == NULL) {
        m_rotate = (GLfloat *) malloc(3 * sizeof(GLfloat));
    }

    m_rotate[0] = x;
    m_rotate[1] = y;
    m_rotate[2] = z;
}

bool Mesh::getRotate(GLfloat *x, GLfloat *y, GLfloat *z){
	if (m_rotate != NULL){
		*x = m_rotate[0];
		*y = m_rotate[1];
		*z = m_rotate[2];
		return true;
	}

	return false;
}


void Mesh::setScale(GLfloat x, GLfloat y, GLfloat z) {
    if (m_scale == NULL) {
        m_scale = (GLfloat *) malloc(3 * sizeof(GLfloat));
    }

    m_scale[0] = x;
    m_scale[1] = y;
    m_scale[2] = z;
}

bool Mesh::getScale(GLfloat *x, GLfloat *y, GLfloat *z){
	if (m_scale != NULL){
		*x = m_scale[0];
		*y = m_scale[1];
		*z = m_scale[2];
		return true;
	}

	return false;
}

void Mesh::initGlCmds() {

	if (m_blendEnabled) {
     	//glDepthMask(GL_FALSE);
      	//glDepthFunc(GL_EQUAL);
		glDisable(GL_DEPTH_TEST);

      	glBlendFunc(m_blendSFactor, m_blendDFactor);
      	glEnable(GL_BLEND);

	}
	else {
     	//glDepthMask(GL_TRUE);
      	//glDepthFunc(GL_LESS);
      	glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
	}

}


void Mesh::renderMesh() {


	if (!m_enabled)
    	return;

    glPushMatrix();

    //enable or disable gl command status
    initGlCmds();

	//use matrix
	if (m_matrix != NULL) 
		glMultMatrixf (m_matrix);

    if (m_position != NULL) {
        glTranslatef(m_position[0], m_position[1], m_position[2]);
    }


    if (m_rotate != NULL) {
        //ratate x axis
        if (m_rotate[0] != 0.0f)
             glRotatef(m_rotate[0], 1.0f, 0.0f, 0.0f);
        //ratate y axis
        if (m_rotate[1] != 0.0f)
             glRotatef(m_rotate[1], 0.0f, 1.0f, 0.0f);
        //ratate z axis
        if (m_rotate[2] != 0.0f)
           	glRotatef(m_rotate[2], 0.0f, 0.0f, 1.0f);
    }

    if (m_scale != NULL)
       	glScalef(m_scale[0], m_scale[1], m_scale[2]);


    if (m_vertices != NULL){
        glEnableClientState(GL_VERTEX_ARRAY);
       	glVertexPointer(3, GL_FLOAT, 0, m_vertices);
	}
    else 
       	return;
        

    if (m_normals != NULL) {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, 0, m_normals);
	}

    if (m_uvs != NULL && m_textureId != -1) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, 0, m_uvs);
    } else {
        glDisable(GL_TEXTURE_2D);
        if ((m_uvs != NULL && m_textureId == -1) ||
            (m_uvs == NULL && m_textureId != -1) ) {
			printf("Only have uvs or texture id!\n");
        }
    }



    if (m_colors != NULL) {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, m_colors);
	}



    //Add for light/material
    if (m_materialAmbient != NULL) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_materialAmbient);

        _M3D_PRINTF ("ambient: r = %g, g = %g, b = %g.\n", m_materialAmbient[0], m_materialAmbient[1], m_materialAmbient[2]);

    }

    if (m_materialDiffuse != NULL){
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_materialDiffuse);
        _M3D_PRINTF ("diffuse: r = %g, g = %g, b = %g.\n", m_materialDiffuse[0], m_materialDiffuse[1], m_materialDiffuse[2]);

    }

    if (m_materialSpecular != NULL) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_materialSpecular);
      	_M3D_PRINTF ("specular: r = %g, g = %g, b = %g.\n", m_materialSpecular[0], m_materialSpecular[1], m_materialSpecular[2]);

    }


    if (m_materialEmission != NULL) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_materialEmission);

      _M3D_PRINTF ("emission: r = %g, g = %g, b = %g.\n", m_materialEmission[0], m_materialEmission[1], m_materialEmission[2]);

	}


    if (m_materialShininess != NULL) {
        glMaterialfv (GL_FRONT_AND_BACK, GL_SHININESS, m_materialShininess);
      	_M3D_PRINTF ("shininess: s = %g.\n", m_materialShininess[0]);

    }


    //dump indices

    if (m_indices != NULL){
    	for (int i = 0; i < m_triangleNums * 3; i++) {
        	_M3D_PRINTF ("indices[%d] = %d. \n", i, m_indices[i]);
    	}
	}

    //dump vertices
    for (int i = 0; i < 6 * 3; i++) {
        _M3D_PRINTF ("m_vertices[%d] = %g. \n", i, m_vertices[i]);
    }




    //end light/material

    if (m_indices != NULL){
        glDrawElements(m_renderPrimitivesMode, m_triangleNums * 3, GL_UNSIGNED_SHORT, m_indices);
        //glDrawElements(GL_TRIANGLES, m_triangleNums * 3, GL_UNSIGNED_SHORT, m_indices);
	}
    else {
        glDrawArrays(m_renderPrimitivesMode, 0, m_triangleNums * 3);
        //glDrawArrays(GL_TRIANGLES, 0, m_triangleNums * 3);
	}

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    //restore matrix
    glPopMatrix();


    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );


}

//Add for light/material

void Mesh::setMaterialAmbient(GLfloat r, GLfloat g, GLfloat b) {
    if (m_materialAmbient == NULL) {
        m_materialAmbient = (GLfloat *) malloc(4 * sizeof(GLfloat));
    }

    m_materialAmbient[0] = r;
    m_materialAmbient[1] = g;
    m_materialAmbient[2] = b;
    m_materialAmbient[3] = 1.0;

}

void Mesh::setMaterialDiffuse(GLfloat r, GLfloat g, GLfloat b) {
    if (m_materialDiffuse == NULL) {
        m_materialDiffuse = (GLfloat *) malloc(4 * sizeof(GLfloat));
    }

    m_materialDiffuse[0] = r;
    m_materialDiffuse[1] = g;
    m_materialDiffuse[2] = b;
    m_materialDiffuse[3] = 1.0;

}


void Mesh::setMaterialSpecular(GLfloat r, GLfloat g, GLfloat b) {
    if (m_materialSpecular == NULL) {
        m_materialSpecular = (GLfloat *) malloc(4 * sizeof(GLfloat));
    }

    m_materialSpecular[0] = r;
    m_materialSpecular[1] = g;
    m_materialSpecular[2] = b;
    m_materialSpecular[3] = 1.0;
}


void Mesh::setMaterialShininess(GLfloat s) {
    if (m_materialShininess == NULL) {
        m_materialShininess = (GLfloat *) malloc(1 * sizeof(GLfloat));
    }

    m_materialShininess[0] = s;
}


void Mesh::setMaterialEmission(GLfloat r, GLfloat g, GLfloat b) {
    if (m_materialEmission == NULL) {
        m_materialEmission = (GLfloat *) malloc(4 * sizeof(GLfloat));
    }

    m_materialEmission[0] = r;
    m_materialEmission[1] = g;
    m_materialEmission[2] = b;
    m_materialEmission[3] = 0.0;

}


//end of light/material

void Mesh::enableBlend (GLboolean enabled) {
	m_blendEnabled = enabled;
}

void Mesh::setBlendFunc (GLenum sfactor, GLenum dfactor) {

	m_blendSFactor = sfactor;
	m_blendDFactor = dfactor;
		
}

#ifdef MATRIX4X4

void Mesh::setMatrix (MMatrix4x4 &m){

    if (m_matrix == NULL) {
        m_matrix = (GLfloat *) malloc(4 * 4 * sizeof(GLfloat));
    }

	const mdouble *p = m.data();
	for (int i = 0; i < 16; i++)
		m_matrix[i] = (GLfloat)p [i];	

}

#else

void Mesh::setMatrix (float* m){

    if (m_matrix == NULL) {
        m_matrix = (GLfloat *) malloc(4 * 4 * sizeof(GLfloat));
    }

	for (int i = 0; i < 16; i++)
		m_matrix[i] = (GLfloat)m [i];	
}


#endif


void Mesh::setRenderPrimitivesMode (GLenum mode){

	m_renderPrimitivesMode = mode;
}


void Mesh::getRenderObject (M3DRenderObject *ob)
{

	if (m_vertices){
		ob->m_vertices = m_vertices;
	}
	//if glDrawArrays will use m_vertexCount
	ob->m_vertexCount = m_triangleNums * 3;


	if (m_indices){
		ob->m_useIndex = true;
		ob->m_indices = m_indices;
	}
	else {
		ob->m_useIndex = false;
		
	}
	ob->m_indexCount = m_triangleNums * 3;

	if (m_colors)
		ob->m_colors = m_colors;

	if (m_normals)
		ob->m_normals = m_normals;

	if (m_uvs)
		ob->m_uvs = m_uvs;

	if (m_textureId != -1)
		ob->m_textureId = m_textureId;


	if (m_materialAmbient)
		ob->m_materialAmbient = m_materialAmbient;

	if (m_materialDiffuse)
		ob->m_materialDiffuse = m_materialDiffuse;
	
	if (m_materialSpecular)
		ob->m_materialSpecular = m_materialSpecular;

	if (m_materialEmission)
		ob->m_materialEmission = m_materialEmission;

	if (m_materialShininess)
		ob->m_materialShininess = m_materialShininess;


	if (m_position)
		ob->m_position = m_position;

	if (m_rotate)
		ob->m_rotate = m_rotate;

	if (m_scale)
		ob->m_scale = m_scale;

	
    ob->m_blendEnabled = m_blendEnabled;
    ob->m_blendSFactor = m_blendSFactor;
    ob->m_blendDFactor = m_blendDFactor;

	ob->m_hardwareVertexBuffer = m_hardwareVertexBuffer;
	ob->m_hardwareIndexBuffer = m_hardwareIndexBuffer;

	ob->m_positionSizeInBytes = m_positionSizeInBytes;
	ob->m_colorSizeInBytes = m_colorSizeInBytes;
	ob->m_uvSizeInBytes = m_uvSizeInBytes;

}

void Mesh::createVBO (size_t sizeInBytesVertex, size_t sizeInBytesIndex)
{
	if (sizeInBytesVertex > 0)
		m_hardwareVertexBuffer = new M3DHardwareVertexBuffer (sizeInBytesVertex, NULL, GL_STATIC_DRAW);

	if (sizeInBytesIndex > 0)
		m_hardwareIndexBuffer = new M3DHardwareIndexBuffer (sizeInBytesIndex, NULL, GL_STATIC_DRAW);
}

void Mesh::destroyVBO ()
{
	if (m_hardwareVertexBuffer)
		delete m_hardwareVertexBuffer;

	if (m_hardwareIndexBuffer)
		delete m_hardwareIndexBuffer;

}



Model::Model() :
    m_meshs(NULL),
    m_meshCount(0) {

	m_meshs = NULL;
	m_meshCount = 0;
}

Model::~Model() {
    delete [] m_meshs;
    //free(m_meshs);
	m_meshs = NULL;
}

void Model::setVertices(GLfloat *vertices, int size, int meshIndex) {
    m_meshs[meshIndex].setVertices(vertices, size);
}

void Model::setNormals(GLfloat *normals, int size, int meshIndex) {
    m_meshs[meshIndex].setNormals(normals, size);
}

void Model::setUvs(GLfloat *uvs, int size, int meshIndex) {
    m_meshs[meshIndex].setUvs(uvs, size);
}

void Model::setColors(GLubyte *colors, int size, int meshIndex) {
    m_meshs[meshIndex].setColors(colors, size);
}

void Model::setIndices(GLshort *indices, int size, int meshIndex) {
    m_meshs[meshIndex].setIndices(indices, size);
}

void Model::setTriangleNums(GLint triangleNums, int meshIndex) {
    m_meshs[meshIndex].setTriangleNums(triangleNums);
}

void Model::setEnabled(GLboolean enabled, int meshIndex) {
    m_meshs[meshIndex].setEnabled(enabled);
}

void Model::setTextureId(GLint textureId, int meshIndex) {
    m_meshs[meshIndex].setTextureId(textureId);
}

void Model::setPosition(GLfloat x, GLfloat y, GLfloat z) {
    for (int i = 0; i < m_meshCount; i++) {
        m_meshs[i].setPosition(x, y, z);
    }
}


//Return false if no position data
bool Model::getPosition(GLfloat *x, GLfloat *y, GLfloat *z, int meshIndex){
	if (m_meshCount > 0) {
		return m_meshs[meshIndex].getPosition (x, y, z);
	}
	return false;
}

void Model::setRotate(GLfloat x, GLfloat y, GLfloat z) {
    for (int i = 0; i < m_meshCount; i++) {
        m_meshs[i].setRotate(x, y, z);
    }
}

//Return false if no rotate data
bool Model::getRotate(GLfloat *x, GLfloat *y, GLfloat *z, int meshIndex){
	if (m_meshCount > 0) {
		return m_meshs[meshIndex].getRotate (x, y, z);
	}
	return false;
}

void Model::setScale(GLfloat x, GLfloat y, GLfloat z) {
    for (int i = 0; i < m_meshCount; i++) {
        m_meshs[i].setScale(x, y, z);
    }
}

//Return false if no scale data
bool Model::getScale(GLfloat *x, GLfloat *y, GLfloat *z, int meshIndex){
	if (m_meshCount > 0) {
		return m_meshs[meshIndex].getScale (x, y, z);
	}
	return false;
}

void Model::setMeshCount(int meshCount) {

	//Fixme: Maybe memory leam. mesh's member do not be free.
    if (m_meshs != NULL) {
        free(m_meshs);
		m_meshs = NULL;
        //delete[] m_meshs;
    }

    if (meshCount > 0) {
#ifdef DEBUG
        printf("Model create [%d] meshs ...\n", meshCount);
#endif
        m_meshCount = meshCount;
        // create meshs
		m_meshs = (Mesh *) malloc(meshCount * sizeof (Mesh));
        memset(m_meshs, 0, meshCount * sizeof (Mesh));
		for (int i = 0; i < meshCount; i++)
			m_meshs[i].initMemberVars();
        //m_meshs = new Mesh[m_meshCount];
    }
}

int Model::getMeshCount() {
    return m_meshCount;
}

void Model::renderModel() {
    //enable or disable gl command status
/*
    for (int i = 0; i < m_meshCount; i++) {
        m_meshs[i].renderMesh();
	}
*/
	M3DRenderer *renderer = new M3DRenderer ();

	for (int i = 0; i < m_meshCount; i++) {

		M3DRenderObject *ob = new M3DRenderObject ();
		m_meshs[i].getRenderObject (ob);
		renderer->render(ob);
		delete (ob);
	}

	delete (renderer);




}


//Add for light/material
void Model::setMaterialAmbient(GLfloat r, GLfloat g, GLfloat b, int meshIndex) {

    m_meshs[meshIndex].setMaterialAmbient(r, g, b);

}


void Model::setMaterialDiffuse(GLfloat r, GLfloat g, GLfloat b, int meshIndex) {

    m_meshs[meshIndex].setMaterialDiffuse(r, g, b);

}


void Model::setMaterialSpecular(GLfloat r, GLfloat g, GLfloat b, int meshIndex) {

    m_meshs[meshIndex].setMaterialSpecular(r, g, b);

}


void Model::setMaterialShininess(GLfloat s, int meshIndex) {

    m_meshs[meshIndex].setMaterialShininess(s);

}

void Model::setMaterialEmission(GLfloat r, GLfloat g, GLfloat b, int meshIndex) {

    m_meshs[meshIndex].setMaterialEmission(r, g, b);

}


void Model::enableBlend (GLboolean enabled, int meshIndex) {
    m_meshs[meshIndex].enableBlend(enabled);
}


void Model::setBlendFunc (GLenum sfactor, GLenum dfactor, int meshIndex){
    m_meshs[meshIndex].setBlendFunc(sfactor, dfactor);
}

#ifdef MATRIX4X4

void Model::setMatrix (MMatrix4x4 &m){

    for (int i = 0; i < m_meshCount; i++) {
		m_meshs[i].setMatrix (m);
    }

}
#else

void Model::setMatrix (float *m){

    for (int i = 0; i < m_meshCount; i++) {
		m_meshs[i].setMatrix (m);
    }

}


#endif

void Model::setRenderPrimitivesMode (GLenum mode, int meshIndex){
    m_meshs[meshIndex].setRenderPrimitivesMode(mode);
}



GLfloat* Mesh::getVertices ()
{
	return m_vertices;
}

GLfloat* Mesh::getNormals ()
{
	return m_normals;
}

GLfloat* Mesh::getUvs ()
{
	return m_uvs;
}

GLubyte* Mesh::getColors ()
{
	return m_colors;
}

GLshort* Mesh::getIndices ()
{
	return m_indices;
}

int Mesh::getTriangleNum ()
{
	return m_triangleNums;
}



void Model::createVBO (size_t sizeInBytesVertex, size_t sizeInBytesIndex, int meshIndex)
{
	
    m_meshs[meshIndex].createVBO(sizeInBytesVertex, sizeInBytesIndex);
}

void Model::destroyVBO ()
{
	for (int i = 0; i < m_meshCount; i++) {
		m_meshs[i].destroyVBO ();
	}

}




M3D_END_NAMESPACE
