/*
 * Copy
*/

#include "M3DHardwareVertexBuffer.h"


M3D_BEGIN_NAMESPACE

M3DHardwareVertexBuffer::M3DHardwareVertexBuffer(size_t sizeInBytes, 
				const void* pSource, GLenum usage)
{

	m_sizeInBytes = sizeInBytes;
	//m_sizeInBytes = numVertices * vertexSize;
	
	glGenBuffers(1, &m_bufferId);
    GL_CHECK_ERROR;

    if (!m_bufferId)
    {
        _M3D_PRINTF ("Cannot create GL vertex buffer");
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
    GL_CHECK_ERROR;
	if (pSource != NULL)
    	glBufferData(GL_ARRAY_BUFFER, m_sizeInBytes, pSource, usage);
	else
    	glBufferData(GL_ARRAY_BUFFER, m_sizeInBytes, NULL, usage);
    GL_CHECK_ERROR;
}

M3DHardwareVertexBuffer::~M3DHardwareVertexBuffer()
{
    glDeleteBuffers(1, &m_bufferId);
    //GL_CHECK_ERROR;
}


void M3DHardwareVertexBuffer::readData(size_t offset, size_t length,
        void* pDest)
{
	return;
}

void M3DHardwareVertexBuffer::writeData(size_t offset, size_t length,
		const void* pSource, GLenum usage, bool discardWholeBuffer)
{
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
        //GL_CHECK_ERROR;


        if (offset == 0 && length == m_sizeInBytes)
        {
            glBufferData(GL_ARRAY_BUFFER, m_sizeInBytes, pSource, usage);
            //GL_CHECK_ERROR;
        }
        else
        {
            if(discardWholeBuffer)
            {
                glBufferData(GL_ARRAY_BUFFER, m_sizeInBytes, NULL,  usage);
            }

            glBufferSubData(GL_ARRAY_BUFFER, offset, length, pSource);
            //GL_CHECK_ERROR;
        }
}



M3D_END_NAMESPACE
