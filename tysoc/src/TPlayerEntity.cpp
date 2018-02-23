
#include <TPlayerEntity.h>


namespace tysoc
{


    TPlayerEntity::TPlayerEntity()
        : TEntity()
    {
        addComponent( new TBasicGraphicsComponent( this ) );
        addComponent( new TBasicPhysicsComponent( this ) );

        m_movSpeed = 0.0f;
        m_movDirection = engine::LVec3( 1, 0, 0 );
        m_isJumping = false;

        setMovementSpeed( m_movSpeed, m_movDirection );
    }

    TPlayerEntity::TPlayerEntity( const engine::LVec3& initialPosition )
        : TEntity( initialPosition )
    {
        addComponent( new TBasicGraphicsComponent( this ) );
        addComponent( new TBasicPhysicsComponent( this ) );

        m_movSpeed = 2.5f;
        m_movDirection = engine::LVec3( 1, 0, 0 );
        m_isJumping = false;

        setMovementSpeed( m_movSpeed, m_movDirection );
    }

    TPlayerEntity::~TPlayerEntity()
    {

    }



    void TPlayerEntity::setMovementSpeed( float movSpeed, engine::LVec3 direction )
    {
        m_movSpeed = movSpeed;
        m_movDirection = direction;

        auto _physics = getComponent< TBasicPhysicsComponent >();
        _physics->getRigidBody()->setLinearVelocity( btVector3( m_movSpeed * m_movDirection.x,
                                                                m_movSpeed * m_movDirection.y,
                                                                m_movSpeed * m_movDirection.z ) );
    }

    void TPlayerEntity::jump( float force )
    {
        
    }


}