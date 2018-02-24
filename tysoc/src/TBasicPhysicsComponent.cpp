
#include <TBasicPhysicsComponent.h>


using namespace std;

namespace tysoc
{


    TBasicPhysicsComponent::TBasicPhysicsComponent( TEntity* pParent )
        : TPhysicsComponent( pParent )
    {
        this->type = TBasicPhysicsComponent::getStaticType();

        btTransform _rbTransform;
        _rbTransform.setIdentity();

        _rbTransform.setOrigin( btVector3( pParent->pos.x,
                                           pParent->pos.y,
                                           pParent->pos.z ) );

        glm::quat _qOrientation = glm::quat_cast( pParent->rotation );
        _rbTransform.setRotation( btQuaternion( _qOrientation.w, 
                                                _qOrientation.x,
                                                _qOrientation.y,
                                                _qOrientation.z ) );

        auto _rbMotionState = new btDefaultMotionState( _rbTransform );

        auto _rbShape = new btSphereShape( 0.2 );
        // auto _rbMotionState = new btDefaultMotionState( btTransform( btQuaternion( 0, 0, 0, 1 ), 
        //                                                              btVector3( pParent->pos.x,
        //                                                                         pParent->pos.y,
        //                                                                         pParent->pos.z ) ) );

        btScalar _rbMass = 2.0f;
        btVector3 _rbInertia( 0, 0, 0 );
        _rbShape->calculateLocalInertia( _rbMass, _rbInertia );

        btRigidBody::btRigidBodyConstructionInfo _rbConstructionInfo( _rbMass, 
                                                                      _rbMotionState, 
                                                                      _rbShape, 
                                                                      _rbInertia );

        m_rBody = new btRigidBody( _rbConstructionInfo );
        m_rBody->setRestitution( 0.5 );
        m_rBody->setFriction( 1.0 );
    }

    TBasicPhysicsComponent::TBasicPhysicsComponent( TEntity* pParent, btRigidBody* pRigidBody )
        : TPhysicsComponent( pParent )
    {
        m_rBody = pRigidBody;
    }

    TBasicPhysicsComponent::~TBasicPhysicsComponent()
    {
        delete m_rBody->getMotionState();
        delete m_rBody;
    }

    void TBasicPhysicsComponent::update( float dt )
    {
        // cout << "update physics" << endl;

        if ( m_parent->inFreeMovement() )
        {
            return;
        }

        btTransform _trans;
        m_rBody->getMotionState()->getWorldTransform( _trans );
        auto _pos = _trans.getOrigin();
        
        // cout << "x: " << _pos.x() << " - y: " << _pos.y() << " - z: " << _pos.z() << endl;
        
        m_parent->pos = engine::LVec3( _pos.x(), _pos.y(), _pos.z() );

        // TODO: add rotation
        
    }

    void TBasicPhysicsComponent::applyForce( const TVec3& force )
    {
        m_rBody->setActivationState( ACTIVE_TAG );
        m_rBody->applyCentralForce( btVector3( force.x, force.y, force.z ) );
    }

    void TBasicPhysicsComponent::applyImpulse( const TVec3& impulse )
    {
        m_rBody->setActivationState( ACTIVE_TAG );
        m_rBody->applyCentralImpulse( btVector3( impulse.x, impulse.y, impulse.z ) );
    }

    TVec3 TBasicPhysicsComponent::getVelocity()
    {
        btVector3 _velocity = m_rBody->getLinearVelocity();
        return TVec3( _velocity.x(), _velocity.y(), _velocity.z() );
    }




}