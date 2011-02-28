/*
 * Copy
*/

#include "M3DHardwareIndexBuffer.h"

M3D_BEGIN_NAMESPACE


M3DHardwareIndexBuffer::M3DHardwareIndexBuffer(size_t sizeInBytes, const void* pSource, GLenum usage)
{

	m_sizeInBytes = sizeInBytes;
	//m_sizeInBytes = numIndices * indexSize;

	glGenBuffers(1, &m_bufferId);
    //GL_CHECK_ERROR;

    if (!m_bufferId)
   	{
        _M3D_PRINTF ("Cannot create GL index buffer");
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
    //GL_CHECK_ERROR;
	if (pSource)
    	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_sizeInBytes, pSource, usage);
	else
    	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_sizeInBytes, NULL, usage);
    //GL_CHECK_ERROR;
}

M3DHardwareIndexBuffer::~M3DHardwareIndexBuffer()
{
    glDeleteBuffers(1, &m_bufferId);
    //GL_CHECK_ERROR;
}


void M3DHardwareIndexBuffer::readData(size_t offset,
		size_t length, void* pDest)
{
}

void M3DHardwareIndexBuffer::writeData(size_t offset, size_t length,
				const void* pSource, GLenum usage, bool discardWholeBuffer)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
    //GL_CHECK_ERROR;


    if (offset == 0 && length == m_sizeInBytes)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_sizeInBytes, pSource, usage);
        //GL_CHECK_ERROR;
    }
    else
    {
        if (discardWholeBuffer)
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_sizeInBytes, NULL, usage);
        }

            // Now update the real buffer
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, length, pSource);
        //GL_CHECK_ERROR;
    }
}



M3D_END_NAMESPACE
