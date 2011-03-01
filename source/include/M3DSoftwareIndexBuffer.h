/*
 * Copy
*/

#ifndef _M3DSOFTWAREINDEXBUFFER_H
#define _M3DSOFTWAREINDEXBUFFER_H

#include "m3d.h"
#include "log.h"


M3D_BEGIN_NAMESPACE

class M3DSoftwareIndexBuffer
{

private:
	unsigned char* m_pData;
	size_t m_sizeInBytes;

public:

    M3DSoftwareIndexBuffer(size_t sizeInBytes);
    ~M3DSoftwareIndexBuffer();

    void readData(size_t offset, size_t length, void* pDest);
    void writeData(size_t offset, size_t length, const void* pSource);
	void* getDataPtr (size_t offset) const { return (void*)(m_pData+offset); }


};


M3D_END_NAMESPACE

#endif
