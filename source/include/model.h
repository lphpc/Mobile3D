
#ifndef _MODEL_H
#define _MODEL_H

#include "m3d.h"

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


    GLboolean   m_blendEnabled;
    GLenum      m_blendSFactor;
    GLenum      m_blendDFactor;

	GLfloat     *m_matrix;
		
    GLenum      m_renderPrimitivesMode;


    GLfloat     *m_position2;

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

	//add for temp
    void setPosition2(GLfloat x, GLfloat y, GLfloat z);

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

	//add for temp
    void setPosition2(GLfloat x, GLfloat y, GLfloat z);

    void renderModel();

    //add for light/material
    void setMaterialAmbient(GLfloat r, GLfloat g, GLfloat b, int meshIndex = 0);
    void setMaterialDiffuse(GLfloat r, GLfloat g, GLfloat b, int meshIndex = 0);
    void setMaterialSpecular(GLfloat r, GLfloat g, GLfloat b, int meshIndex = 0);
    void setMaterialEmission(GLfloat r, GLfloat g, GLfloat b, int meshIndex = 0);
    void setMaterialShininess(GLfloat s, int meshIndex = 0);

		
	void enableBlend (GLboolean enabled, int meshIndex = 0);
	void setBlendFunc (GLenum sfactor, GLenum dfactor, int meshIndex = 0);

#ifdef MATRIX4X4
	void setMatrix (MMatrix4x4 &m);
#else
	void setMatrix (float *m);
#endif

	void setRenderPrimitivesMode (GLenum mode, int meshIndex = 0);
};


M3D_END_NAMESPACE

#endif
