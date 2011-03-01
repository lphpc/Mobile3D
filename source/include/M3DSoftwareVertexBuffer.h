/*
COPY
*/

#ifndef _M3D_SOFTWAREVERTEXBUFFER_H
#define _M3D_SOFTWAREVERTEXBUFFER_H

#include "m3d.h"
#include "log.h"

M3D_BEGIN_NAMESPACE

class M3DSoftwareVertexBuffer
{
private:
	size_t m_sizeInBytes;
	unsigned char* m_pData;


public:
    M3DSoftwareVertexBuffer(size_t sizeInBytes);
    ~M3DSoftwareVertexBuffer();

    void readData(size_t offset, size_t length, void* pDest);
    void writeData(size_t offset, size_t length, const void* pSource);

	void* getDataPtr (size_t offset) const { return (void*)(m_pData+offset); }
};

M3D_END_NAMESPACE

#endif
