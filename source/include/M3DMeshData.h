/*
COPY
*/

#ifndef _M3D_MESHDATA_H
#define _M3D_MESHDATA_H

#include "m3d.h"
#include "log.h"

M3D_BEGIN_NAMESPACE

class M3DMeshData
{
public:

    GLfloat     *m_vertices;
    GLfloat     *m_normals;
    GLfloat     *m_uvs;
    GLubyte     *m_colors;
    GLshort     *m_indices;
	
	size_t m_vertexCount;
	size_t m_indexCount;
	size_t m_triangleCount;

 	size_t m_positionSizeInBytes;
	size_t m_colorSizeInBytes;
	size_t m_uvSizeInBytes;
	size_t m_normalSizeInBytes;



public:
    M3DMeshData ();
    ~M3DMeshData ();

    void setVertices(GLfloat *vertices, size_t vertexSize, size_t vertexCount);
    void setNormals(GLfloat *normals, size_t sizeInBytes);
    void setUvs(GLfloat *uvs, size_t sizeInBytes);
    void setColors(GLubyte *colors, size_t sizeInBytes);
    void setIndices(GLshort *indices, size_t indexSize, size_t indexCount);
	void setTriangleNums(size_t triangleCount);

};

M3D_END_NAMESPACE

#endif
