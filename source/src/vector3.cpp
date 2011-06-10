/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2005 The OGRE Team
Also see acknowledgements in Readme.html

-----------------------------------------------------------------------------
*/
//#include "OgreStableHeaders.h"
#include "vector3.h"
#include "math.h"


M3D_BEGIN_NAMESPACE

    const Vector3 Vector3::ZERO( 0, 0, 0 );

    const Vector3 Vector3::UNIT_X( 1, 0, 0 );
    const Vector3 Vector3::UNIT_Y( 0, 1, 0 );
    const Vector3 Vector3::UNIT_Z( 0, 0, 1 );
    const Vector3 Vector3::NEGATIVE_UNIT_X( -1,  0,  0 );
    const Vector3 Vector3::NEGATIVE_UNIT_Y(  0, -1,  0 );
    const Vector3 Vector3::NEGATIVE_UNIT_Z(  0,  0, -1 );
    const Vector3 Vector3::UNIT_SCALE(1, 1, 1);

M3D_END_NAMESPACE
