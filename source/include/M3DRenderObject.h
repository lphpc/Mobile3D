
#ifndef _M3D_RENDEROBJECT_H
#define _M3D_RENDEROBJECT_H

#include "m3d.h"
#include "M3DHardwareVertexBuffer.h"
#include "M3DHardwareIndexBuffer.h"

M3D_BEGIN_NAMESPACE

class M3DRenderObject {

public:

	enum PrimitiveType {
	
		PT_POINTS = 1, 
		PT_LINE_STRIP = 2, 
		PT_LINE_LOOP = 3, 
		PT_LINES = 4, 
		PT_TRIANGLES = 5,
		PT_TRIANGLE_STRIP = 6, 
		PT_TRIANGLE_FAN = 7, 
	};

	bool m_useIndex;
	PrimitiveType m_primType;

    GLfloat *m_vertices;
	int     m_vertexCount;
    
    GLshort *m_indices;
	int     m_indexCount;

    GLubyte *m_colors;

    GLfloat *m_normals;
    GLfloat *m_uvs;
    GLint   m_textureId;

    GLfloat     *m_materialAmbient;
    GLfloat     *m_materialDiffuse;
    GLfloat     *m_materialSpecular;
    GLfloat     *m_materialEmission;
    GLfloat     *m_materialShininess;



    GLfloat *m_position;
    GLfloat *m_rotate;
    GLfloat *m_scale;

    GLboolean   m_blendEnabled;
    GLenum      m_blendSFactor;
    GLenum      m_blendDFactor;


	M3DHardwareVertexBuffer *m_hardwareVertexBuffer;
	M3DHardwareIndexBuffer *m_hardwareIndexBuffer;

	size_t m_positionSizeInBytes;
	size_t m_colorSizeInBytes;
	size_t m_uvSizeInBytes;


public:
    M3DRenderObject();
    ~M3DRenderObject();
 
};



M3D_END_NAMESPACE

#endif
