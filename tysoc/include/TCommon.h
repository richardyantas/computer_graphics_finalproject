
#pragma once

#define BT_USE_DOUBLE_PRECISION
#include <btBulletDynamicsCommon.h>

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <cassert>

#define MAX_DELTA 0.05

#define _RAND_FLOAT_RANGE( a, b ) ( a + ( b - a ) * ( rand() / ( float )RAND_MAX ) )
#define _RAND_INT_RANGE( a, b ) ( a + rand() % ( b - a + 1 ) )

#include <LCommon.h>

namespace tysoc
{

    typedef engine::LVec3 TVec3;


    enum _primitiveCollisionType
    {
        COLLISION_SPHERE,
        COLLISION_BOX,
        COLLISION_CYLINDER,
        COLLISION_CAPSULE
    };

    enum _primitiveGraphicsType
    {
        GRAPHICS_SPHERE,
        GRAPHICS_BOX,
        GRAPHICS_CYLINDER,
        GRAPHICS_CAPSULE
    };
            

}