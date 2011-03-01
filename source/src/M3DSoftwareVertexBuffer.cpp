/*
 * Copy
*/

#include "M3DSoftwareVertexBuffer.h"


M3D_BEGIN_NAMESPACE

M3DSoftwareVertexBuffer::M3DSoftwareVertexBuffer(size_t sizeInBytes)
{

	m_sizeInBytes = sizeInBytes;
	//m_sizeInBytes = numVertices * vertexSize;
	m_pData = new unsigned char [m_sizeInBytes];	
}

M3DSoftwareVertexBuffer::~M3DSoftwareVertexBuffer()
{
	delete [] m_pData;
}


void M3DSoftwareVertexBuffer::readData(size_t offset, size_t length,
        void* pDest)
{
	return;
}

void M3DSoftwareVertexBuffer::writeData(size_t offset, size_t length, const void* pSource)
{
	//overflow
	if ((offset+length) > m_sizeInBytes)
		return;

	memcpy (m_pData + offset, pSource, length);

}



M3D_END_NAMESPACE
