
#pragma once

#include "TEntity.h"
#include "TBasicGraphicsComponent.h"
#include "TBasicPhysicsComponent.h"
#include <LInputHandler.h>

namespace tysoc
{


    class TPlayerEntity : public TEntity
    {

        private :

        bool m_isJumping;

        float m_movSpeed;
        engine::LVec3 m_movDirection;

        public :

        TPlayerEntity();
        TPlayerEntity( const engine::LVec3& initialPosition );
        ~TPlayerEntity();

        void setMovementSpeed( float movSpeed, engine::LVec3 direction );
        void jump( float force );
    };






    
}