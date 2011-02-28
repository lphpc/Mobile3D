/*
COPY
*/

#ifndef _M3D_HARDWAREVERTEXBUFFER_H
#define _M3D_HARDWAREVERTEXBUFFER_H

#include "m3d.h"
#include "log.h"

M3D_BEGIN_NAMESPACE

class M3DHardwareVertexBuffer
{
private:
	size_t m_sizeInBytes;

public:
	GLuint m_bufferId;

public:
    M3DHardwareVertexBuffer(size_t sizeInBytes, const void* pSource, GLenum usage);
    //M3DHardwareVertexBuffer(size_t vertexSize, size_t numVertices, const void* pSource, GLenum usage);
    ~M3DHardwareVertexBuffer();

    void readData(size_t offset, size_t length, void* pDest);
    void writeData(size_t offset, size_t length, 
                   const void* pSource, GLenum usage, bool discardWholeBuffer = false);

    GLuint getGLBufferId(void) const { return m_bufferId; }
};

M3D_END_NAMESPACE

#endif
