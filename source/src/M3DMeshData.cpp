/*
 * Copy
*/

#include "M3DMeshData.h"


M3D_BEGIN_NAMESPACE

M3DMeshData::M3DMeshData()
{

    m_vertices = NULL;
    m_normals = NULL;
    m_uvs = NULL;
    m_colors = NULL;
    m_indices = NULL;
	
	m_vertexCount = 0;
	m_indexCount = 0;
	m_triangleCount = 0;

	m_positionSizeInBytes = 0;
	m_colorSizeInBytes = 0;
	m_uvSizeInBytes = 0;
	m_normalSizeInBytes = 0;
 
}

M3DMeshData::~M3DMeshData()
{
	FREEANDNULL (m_vertices);
	FREEANDNULL (m_normals);
	FREEANDNULL (m_uvs);
	FREEANDNULL (m_colors);
	FREEANDNULL (m_indices);
}

void M3DMeshData::setVertices(GLfloat *vertices, size_t vertexSize, size_t vertexCount)
{
	m_positionSizeInBytes = vertexSize * vertexCount;
	m_vertexCount = vertexCount;

    m_vertices = (GLfloat *) malloc(m_positionSizeInBytes);
    memcpy(m_vertices, vertices, m_positionSizeInBytes);

}

void M3DMeshData::setIndices(GLshort *indices, size_t indexSize, size_t indexCount)
{
	size_t indexSizeInBytes = indexSize * indexCount;
	m_indexCount = indexCount;

    m_indices = (GLshort *) malloc(indexSizeInBytes);
    memcpy(m_indices, indices, indexSizeInBytes);
}





void M3DMeshData::setNormals(GLfloat *normals, size_t sizeInBytes)
{
	m_normalSizeInBytes = sizeInBytes;

    m_normals = (GLfloat *) malloc(sizeInBytes);
    memcpy(m_normals, normals, sizeInBytes);

}

void M3DMeshData::setUvs(GLfloat *uvs, size_t sizeInBytes)
{
	m_uvSizeInBytes = sizeInBytes;

    m_uvs = (GLfloat *) malloc(sizeInBytes);
    memcpy(m_uvs, uvs, sizeInBytes);

}

void M3DMeshData::setColors(GLubyte *colors, size_t sizeInBytes)
{

	m_colorSizeInBytes = sizeInBytes;

    m_colors = (GLubyte *) malloc(sizeInBytes);
    memcpy(m_colors, colors, sizeInBytes);

}

void M3DMeshData::setTriangleNums(size_t triangleCount) {
    m_triangleCount = triangleCount;
}




M3D_END_NAMESPACE
