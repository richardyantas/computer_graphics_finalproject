
#pragma once

#include "TPhysicsComponent.h"


using namespace std;

namespace tysoc
{

    struct TPhysicsKinematicsParams
    {
        // sphere params
        float sphere_radius;

        // box params
        float box_width;
        float box_height;
        float box_depth;

        // cylinder params
        float cylinder_baseRadius;
        float cylinder_length;

        // capsule params
        float capsule_baseRadius;
        float capsule_length;
    };

    struct TPhysicsDynamicsParams
    {
        float mass;
        float restitution;
    };


    class TPrimitivePhysicsComponent : public TPhysicsComponent
    {


        private :

        btRigidBody* m_rBody;

        _primitiveCollisionType m_collisionType;

        void _buildBody( _primitiveCollisionType collisionType, 
                        const TPhysicsKinematicsParams& kinParams,
                        const TPhysicsDynamicsParams& dynParams );

        public :

        TPrimitivePhysicsComponent( TEntity* pParent, 
                                    _primitiveCollisionType collisionType, 
                                    const TPhysicsKinematicsParams& kinParams,
                                    const TPhysicsDynamicsParams& dynParams );
        ~TPrimitivePhysicsComponent();

        static string getStaticType() { return string( "basePhysicsComponent" ); }

        void update( float dt ) override;

        btRigidBody* getRigidBody() { return m_rBody; }

        _primitiveCollisionType getCollisionType() { return m_collisionType; }

    };






}






