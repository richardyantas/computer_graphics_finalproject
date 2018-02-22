

#include <TPrimitivePhysicsComponent.h>



using namespace std;

namespace tysoc
{


    TPrimitivePhysicsComponent::TPrimitivePhysicsComponent( TEntity* pParent, 
                                                            _primitiveCollisionType collisionType, 
                                                            const TPhysicsKinematicsParams& kinParams,
                                                            const TPhysicsDynamicsParams& dynParams )
        : TPhysicsComponent( pParent )
    {
        this->type = TPrimitivePhysicsComponent::getStaticType();

        m_rBody = NULL;

        _buildBody( collisionType, kinParams, dynParams );
    }

    void TPrimitivePhysicsComponent::_buildBody( _primitiveCollisionType collisionType, 
                                                const TPhysicsKinematicsParams& kinParams,
                                                const TPhysicsDynamicsParams& dynParams )
    {

        btTransform _rbTransform;
        _rbTransform.setIdentity();

        _rbTransform.setOrigin( btVector3( m_parent->pos.x,
                                           m_parent->pos.y,
                                           m_parent->pos.z ) );

        glm::quat _qOrientation = glm::quat_cast( m_parent->rotation );
        _rbTransform.setRotation( btQuaternion( _qOrientation.x, 
                                                _qOrientation.y,
                                                _qOrientation.z,
                                                _qOrientation.w ) );

        btDefaultMotionState* _rbMotionState = new btDefaultMotionState( _rbTransform );

        btCollisionShape* _rbShape = NULL;
        
        switch ( collisionType )
        {
            case COLLISION_SPHERE :

                _rbShape = new btSphereShape( kinParams.sphere_radius );

            break;

            case COLLISION_BOX :

                _rbShape = new btBoxShape( btVector3( kinParams.box_width / 2,
                                                      kinParams.box_height / 2,
                                                      kinParams.box_depth / 2 ) );

            break;

            case COLLISION_CYLINDER :

                _rbShape = new btCylinderShape( btVector3( kinParams.cylinder_baseRadius,
                                                           kinParams.cylinder_length / 2,
                                                           kinParams.cylinder_baseRadius ) );

            break;

            case COLLISION_CAPSULE :

                _rbShape = new btCapsuleShape( kinParams.capsule_baseRadius,
                                               kinParams.capsule_length );

            break;
        }

        btScalar _rbMass = dynParams.mass;
        btVector3 _rbInertia( 0, 0, 0 );

        _rbShape->calculateLocalInertia( _rbMass, _rbInertia );

        btRigidBody::btRigidBodyConstructionInfo _rbConstructionInfo( _rbMass, 
                                                                      _rbMotionState, 
                                                                      _rbShape, 
                                                                      _rbInertia );

        m_rBody = new btRigidBody( _rbConstructionInfo );
        m_rBody->setRestitution( dynParams.restitution );

    }

    TPrimitivePhysicsComponent::~TPrimitivePhysicsComponent()
    {
        assert( m_rBody != NULL );

        delete m_rBody->getMotionState();
        delete m_rBody;

        m_rBody = NULL;
    }

    void TPrimitivePhysicsComponent::update( float dt )
    {
        btTransform _transform;
        m_rBody->getMotionState()->getWorldTransform( _transform );

        btVector3 _position = _transform.getOrigin();
        btQuaternion _rotation = _transform.getRotation();

        m_parent->pos = TVec3( _position.x(), _position.y(), _position.z() );
        m_parent->rotation = glm::mat4_cast( glm::quat( _rotation.w(), _rotation.x(),
                                                        _rotation.y(), _rotation.z() ) );
    }




}