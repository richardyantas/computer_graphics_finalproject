
#include <TPlayerEntity.h>


namespace tysoc
{


    TPlayerEntity::TPlayerEntity()
        : TEntity()
    {
        addComponent( new TBasicGraphicsComponent( this ) );
        addComponent( new TBasicPhysicsComponent( this ) );

        m_movSpeed = 0.0f;
        m_movDirection = engine::LVec3( 0, 0, 0 );
        m_isJumping = false;
    }

    TPlayerEntity::TPlayerEntity( const engine::LVec3& initialPosition )
        : TEntity( initialPosition )
    {
        addComponent( new TBasicGraphicsComponent( this ) );
        addComponent( new TBasicPhysicsComponent( this ) );

        m_movSpeed = 0.0f;
        m_movDirection = engine::LVec3( 0, 0, 0 );
        m_isJumping = false;
    }

    TPlayerEntity::~TPlayerEntity()
    {

    }



    void TPlayerEntity::setMovementSpeed( float movSpeed, engine::LVec3 direction )
    {
        m_movSpeed = movSpeed;
        m_movDirection = direction;
    }

    void TPlayerEntity::jump( float force )
    {
        
    }


}