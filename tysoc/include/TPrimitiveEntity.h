
#pragma once

#include "TEntity.h"
#include "TPrimitiveGraphicsComponent.h"
#include "TPrimitivePhysicsComponent.h"

namespace tysoc
{


    class TPrimitiveEntity : public TEntity
    {

        public :

        TPrimitiveEntity( const TVec3& initialPosition,
                          const TVec3& initialVelocity,
                          _primitiveGraphicsType graphicsPrimitive,
                          _primitiveCollisionType collisionPrimitive,
                         const TPrimitiveGraphicsParams& gParams,
                         const TPhysicsKinematicsParams& pKynParams,
                         const TPhysicsDynamicsParams& pDynParams );
        ~TPrimitiveEntity();
    };






    
}