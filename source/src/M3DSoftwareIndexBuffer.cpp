/*
 * Copy
*/

#include "M3DSoftwareIndexBuffer.h"

M3D_BEGIN_NAMESPACE


M3DSoftwareIndexBuffer::M3DSoftwareIndexBuffer(size_t sizeInBytes)
{

	m_sizeInBytes = sizeInBytes;
	//m_sizeInBytes = numIndices * indexSize;
	m_pData = new unsigned char [m_sizeInBytes];

}

M3DSoftwareIndexBuffer::~M3DSoftwareIndexBuffer()
{
	delete [] m_pData;
}


void M3DSoftwareIndexBuffer::readData(size_t offset, size_t length, void* pDest)
{
}

void M3DSoftwareIndexBuffer::writeData(size_t offset, size_t length, const void* pSource)
{
	if ((offset + length) > m_sizeInBytes)
		return;

	memcpy (m_pData + offset, pSource, length);
}



M3D_END_NAMESPACE
