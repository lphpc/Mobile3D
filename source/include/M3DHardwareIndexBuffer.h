/*
 * Copy
*/

#ifndef _M3DHardwareIndexBuffer_H
#define _M3DHardwareIndexBuffer_H

#include "m3d.h"
#include "log.h"


M3D_BEGIN_NAMESPACE

class M3DHardwareIndexBuffer
{

private:
	size_t m_sizeInBytes;


public:
	GLuint m_bufferId;

    M3DHardwareIndexBuffer(size_t sizeInBytes, const void* pSource, GLenum usage);
    //M3DHardwareIndexBuffer(IndexType idxType, size_t numIndexes, GLenum usage);
    ~M3DHardwareIndexBuffer();

    void readData(size_t offset, size_t length, void* pDest);
    void writeData(size_t offset, size_t length, 
                const void* pSource, GLenum usage,  bool discardWholeBuffer = false);

    GLuint getGLBufferId(void) const { return m_bufferId; }

};


M3D_END_NAMESPACE

#endif
