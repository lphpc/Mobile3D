
#ifndef _M3D_QUAD_H_
#define _M3D_QUAD_H_

#include "model.h"
#include "imageTGA.h"

M3D_BEGIN_NAMESPACE


/**
 * ModelAM class for all games using M3D.
 */
class M3DQuad {

private:
	Model model;
	int meshCount;
	int triangleCount;
	int vertexCount;
	int uvCount;
	int indexCount;

public:
    M3DQuad ();
    ~M3DQuad ();

    void create (float x, float y, float width, float height, const char *fileName);
    void draw();
	void rotate (float x, float y, float z);
	void translate (float x, float y, float z);
};

M3D_END_NAMESPACE

#endif /* _M3D_QUAD_H_ */
