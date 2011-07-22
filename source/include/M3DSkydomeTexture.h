
/*
 * Skydome with texture.
 */

#ifndef _M3D_SKYDOMETEXTURE_H_
#define _M3D_SKYDOMETEXTYRE_H_

#include "model.h"


M3D_BEGIN_NAMESPACE


    class SkydomeT : public Model {
    public:
        /**
        * Constructor
        */
        SkydomeT(int radius, float dtheta, float dphi);

        /**
         * Destructor
         */
        virtual ~SkydomeT();
    };



M3D_END_NAMESPACE

#endif 
