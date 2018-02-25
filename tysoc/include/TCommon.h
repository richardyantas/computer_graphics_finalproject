
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
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>

#define MAX_DELTA 0.05

#define _RAND_FLOAT_RANGE( a, b ) ( a + ( b - a ) * ( rand() / ( float )RAND_MAX ) )
#define _RAND_INT_RANGE( a, b ) ( a + rand() % ( b - a + 1 ) )

#include <LCommon.h>

#define TERRAIN1D_MATERIAL_AMBIENT_COMPONENT    engine::LVec3( 0.701f, 0.706f, 0.658f )
#define TERRAIN1D_MATERIAL_DIFFUSE_COMPONENT    engine::LVec3( 0.701f, 0.706f, 0.658f )
#define TERRAIN1D_MATERIAL_SPECULAR_COMPONENT   engine::LVec3( 0.701f, 0.706f, 0.658f )
#define TERRAIN1D_MATERIAL_SHININESS_COMPONENT  50.0f

namespace tysoc
{

    typedef engine::LVec3 TVec3;

    struct TAABB
    {
        engine::LVec2 p[4];
    };

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