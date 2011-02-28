
#ifndef M3D_RENDERER_H_
#define M3D_RENDERER_H_

#include "m3d.h"
#include "M3DRenderObject.h"

M3D_BEGIN_NAMESPACE

class M3DRenderer {

private:

public:
    M3DRenderer ();
    ~M3DRenderer ();

	void render (const M3DRenderObject *ob);	
};

M3D_END_NAMESPACE

#endif /* M3D_RENDERER_H_ */
