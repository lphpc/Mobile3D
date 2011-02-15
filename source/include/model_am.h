
#ifndef _M3D_MODELAM_H_
#define _M3D_MODELAM_H_

#include "model.h"

M3D_BEGIN_NAMESPACE


/**
 * ModelAM class for all games using M3D.
 */
class ModelAM : public Model {

public:
    ModelAM ();
    ~ModelAM ();

    void loadModel (const char *filename);

    void renderModel();
};

M3D_END_NAMESPACE

#endif /* _M3D_MODELAM_H_ */
