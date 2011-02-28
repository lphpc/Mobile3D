
#ifndef _MODEL_H
#define _MODEL_H

#include "m3d.h"
#include "M3DRenderObject.h"
#include "M3DRenderer.h"
#include "M3DHardwareVertexBuffer.h"
#include "M3DHardwareIndexBuffer.h"

//#define MATRIX4X4 1

#ifdef MATRIX4X4
#include "math3d.h"
#endif

M3D_BEGIN_NAMESPACE

class Mesh {

protected:
    GLfloat     *m_vertices;
    GLfloat     *m_normals;
    GLfloat     *m_uvs;
    GLubyte     *m_colors;
    GLshort     *m_indices;
    GLfloat     *m_position;
    GLfloat     *m_rotate;
    GLfloat     *m_scale;
    GLint       m_textureId;
    GLint       m_triangleNums;
    GLboolean   m_enabled;

    //Add for light/material
    GLfloat     *m_materialAmbient;
    GLfloat     *m_materialDiffuse;
    GLfloat     *m_materialSpecular;
    GLfloat     *m_materialEmission;
    GLfloat     *m_materialShininess;


	GLfloat     *m_matrix;
		
    GLenum      m_renderPrimitivesMode;

    GLboolean   m_blendEnabled;
    GLenum      m_blendSFactor;
    GLenum      m_blendDFactor;


	M3DHardwareVertexBuffer *m_hardwareVertexBuffer;
	M3DHardwareIndexBuffer *m_hardwareIndexBuffer;

	size_t m_positionSizeInBytes;
	size_t m_colorSizeInBytes;
	size_t m_uvSizeInBytes;


private:
    void initGlCmds();

public:
    Mesh();
    ~Mesh();

	void initMemberVars ();
    void setVertices(GLfloat *vertices, int size);
    void setNormals(GLfloat *normals, int size);
    void setUvs(GLfloat *uvs, int size);
    void setColors(GLubyte *colors, int size);
    void setIndices(GLshort *indices, int size);
    void setTextureId(GLint textureId);
    void setTriangleNums(GLint triangleNums);
    void setEnabled(GLboolean enabled);
    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    bool getPosition(GLfloat *x, GLfloat *y, GLfloat *z);
    void setRotate(GLfloat x, GLfloat y, GLfloat z);
    bool getRotate(GLfloat *x, GLfloat *y, GLfloat *z);
    void setScale(GLfloat x, GLfloat y, GLfloat z);
    bool getScale(GLfloat *x, GLfloat *y, GLfloat *z);

    void renderMesh();

    //Add for light/material
    void setMaterialAmbient (GLfloat r, GLfloat g, GLfloat b);
    void setMaterialDiffuse (GLfloat r, GLfloat g, GLfloat b);
    void setMaterialSpecular (GLfloat r, GLfloat g, GLfloat b);
    void setMaterialEmission (GLfloat r, GLfloat g, GLfloat b);
    void setMaterialShininess (GLfloat s);

	//enable or disenable blending
	void enableBlend (GLboolean enabled);
	void setBlendFunc (GLenum sfactor, GLenum dfactor);

#ifdef MATRIX4X4
	void setMatrix (MMatrix4x4 &m);
#else
	void setMatrix (float *m);
#endif

	void setRenderPrimitivesMode (GLenum mode);

    GLfloat *getVertices ();
    GLfloat *getNormals ();
    GLfloat *getUvs ();
    GLubyte *getColors ();
    GLshort *getIndices ();
	int getTriangleNum ();

	//set mesh data pointer to ob
	void getRenderObject (M3DRenderObject *ob);
	void createVBO (size_t sizeInBytesVertex, size_t sizeInBytesIndex);
	void destroyVBO ();
 
};

class Model {
protected:
    Mesh    *m_meshs;
    int     m_meshCount;

public:
    Model();
    ~Model();

    void setVertices(GLfloat *vertices, int size, int meshIndex = 0);
    void setNormals(GLfloat *normals, int size, int meshIndex = 0);
    void setUvs(GLfloat *uvs, int size, int meshIndex = 0);
    void setColors(GLubyte *colors, int size, int meshIndex = 0);
	void setIndices(GLshort *indices, int size, int meshIndex = 0);
    void setTextureId(GLint textureId, int meshIndex = 0);
    void setTriangleNums(GLint triangleNums, int meshIndex = 0);
    void setEnabled(GLboolean enabled, int meshIndex = 0);
    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    bool getPosition(GLfloat *x, GLfloat *y, GLfloat *z, int meshIndex = 0);
    void setRotate(GLfloat x, GLfloat y, GLfloat z);
    bool getRotate(GLfloat *x, GLfloat *y, GLfloat *z, int meshIndex = 0);
    void setScale(GLfloat x, GLfloat y, GLfloat z);
    bool getScale(GLfloat *x, GLfloat *y, GLfloat *z, int meshIndex = 0);
    void setMeshCount(int meshCount);
    int getMeshCount();

    void renderModel();

    //add for light/material
    void setMaterialAmbient(GLfloat r, GLfloat g, GLfloat b, int meshIndex);
    void setMaterialDiffuse(GLfloat r, GLfloat g, GLfloat b, int meshIndex);
    void setMaterialSpecular(GLfloat r, GLfloat g, GLfloat b, int meshIndex);
    void setMaterialEmission(GLfloat r, GLfloat g, GLfloat b, int meshIndex);
    void setMaterialShininess(GLfloat s, int meshIndex);

		
	void enableBlend (GLboolean enabled, int meshIndex);
	void setBlendFunc (GLenum sfactor, GLenum dfactor, int meshIndex);

#ifdef MATRIX4X4
	void setMatrix (MMatrix4x4 &m);
#else
	void setMatrix (float *m);
#endif

	void setRenderPrimitivesMode (GLenum mode, int meshIndex);


	void createVBO (size_t sizeInBytesVertex, size_t sizeInBytesIndex, int meshIndex);
	void destroyVBO ();

	

};


M3D_END_NAMESPACE

#endif
