
#include <TPrimitiveEntity.h>


namespace tysoc
{

    TPrimitiveEntity::TPrimitiveEntity( const TVec3& initialPosition,
                                        const TVec3& initialVelocity,
                                        _primitiveGraphicsType graphicsPrimitive,
                                        _primitiveCollisionType collisionPrimitive,
                                        const TPrimitiveGraphicsParams& gParams,
                                        const TPhysicsKinematicsParams& pKynParams,
                                        const TPhysicsDynamicsParams& pDynParams )
        : TEntity( initialPosition )
    {
        addComponent( new TPrimitiveGraphicsComponent( this, graphicsPrimitive, gParams ) );
        addComponent( new TPrimitivePhysicsComponent( this, collisionPrimitive, pKynParams, pDynParams ) );
    }

    TPrimitiveEntity::~TPrimitiveEntity()
    {

    }


}