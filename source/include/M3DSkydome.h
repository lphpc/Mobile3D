
#ifndef _M3D_SKYDOME_H_
#define _M3D_SKYDOME_H_

#include "model.h"


M3D_BEGIN_NAMESPACE


    class Skydome : public Model {
    public:
        /**
        * Constructor
        */
        Skydome(int radius, float dtheta, float dphi);

        /**
         * Destructor
         */
        virtual ~Skydome();
    };



M3D_END_NAMESPACE

#endif 
