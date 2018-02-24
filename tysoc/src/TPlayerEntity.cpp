
#include <TPlayerEntity.h>


namespace tysoc
{


    TPlayerEntity::TPlayerEntity()
        : TEntity()
    {
        m_movSpeed = 0.0f;
        m_movDirection = engine::LVec3( 1, 0, 0 );
        m_isJumping = false;
        m_inFreeMovement = false;
        m_timer = 0.0f;


        addComponent( new TBasicGraphicsComponent( this ) );
        addComponent( new TBasicPhysicsComponent( this ) );
        addComponent( new TKeyboardController( this ) );
    }

    TPlayerEntity::TPlayerEntity( const engine::LVec3& initialPosition )
        : TEntity( initialPosition )
    {
        m_movSpeed = 0.0f;
        m_movDirection = engine::LVec3( 1, 0, 0 );
        m_isJumping = false;
        m_inFreeMovement = false;
        m_timer = 0.0f;


        addComponent( new TBasicGraphicsComponent( this ) );
        addComponent( new TBasicPhysicsComponent( this ) );
        addComponent( new TKeyboardController( this ) );
    }

    TPlayerEntity::~TPlayerEntity()
    {

    }

    void TPlayerEntity::setSpeed( float movSpeed )
    {
        if ( m_movSpeed == movSpeed )
        {
            return;
        }

        m_movSpeed = movSpeed;
        auto _physics = getComponent< TBasicPhysicsComponent >();
        _physics->getRigidBody()->setLinearVelocity( btVector3( m_movSpeed * m_movDirection.x,
                                                                m_movSpeed * m_movDirection.y,
                                                                m_movSpeed * m_movDirection.z ) );
    }

    void TPlayerEntity::setForcedPosition( const TVec3& position )
    {
        auto _physics = getComponent< TBasicPhysicsComponent >();
        btMotionState* _mState = _physics->getRigidBody()->getMotionState();

        btTransform _rbTransform;
        _rbTransform.setIdentity();
        _rbTransform.setOrigin( btVector3( position.x,
                                           position.y,
                                           position.z ) );

        _mState->setWorldTransform( _rbTransform );
        _physics->getRigidBody()->setMotionState( _mState );

        this->pos = position;
    }

    void TPlayerEntity::jump( float force )
    {
        if ( m_inFreeMovement )
        {
            return;
        }

        auto _physics = getComponent< TBasicPhysicsComponent >();
        _physics->applyImpulse( TVec3( 0, force, 0 ) );
    }

    void TPlayerEntity::update( float dt )
    {
        TEntity::update( dt );
        m_timer += dt;
        if ( m_timer >= 0.2f )
        {
            m_timer = 0.0f;
            m_trail.append( this->pos );
        }
    }
}