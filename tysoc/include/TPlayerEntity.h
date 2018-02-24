
#pragma once

#include "TEntity.h"
#include "TBasicGraphicsComponent.h"
#include "TBasicPhysicsComponent.h"
#include <controllers/TKeyboardController.h>
#include <LInputHandler.h>
#include <deque>

#define TRAIL_SIZE 100

using namespace std;

namespace tysoc
{
    class TPlayerTrail
    {
        private :

        deque< TVec3 > m_trailPoints;

        public :

        TPlayerTrail()
        {
            
        }

        ~TPlayerTrail()
        {
            m_trailPoints.clear();
        }

        void append( const TVec3& point )
        {
            if ( m_trailPoints.size() < TRAIL_SIZE )
            {
                m_trailPoints.push_back( point );
            }
            else
            {
                m_trailPoints.pop_front();
                m_trailPoints.push_back( point );
            }
        }

        vector< TVec3 > getTrailPoints()
        {
            vector< TVec3 > _vecTrail;

            for ( auto _it = m_trailPoints.begin(); _it != m_trailPoints.end(); _it++ )
            {
                _vecTrail.push_back( *_it );
            }

            return _vecTrail;
        }
    };

    class TKeyboardController;

    class TPlayerEntity : public TEntity
    {

        private :

        bool m_isJumping;

        float m_movSpeed;
        engine::LVec3 m_movDirection;

        TPlayerTrail m_trail;

        float m_timer;

        public :

        TPlayerEntity();
        TPlayerEntity( const engine::LVec3& initialPosition );
        ~TPlayerEntity();

        void jump( float force );

        void setSpeed( float movSpeed );

        void setForcedPosition( const TVec3& position );

        void update( float dt ) override;

        float movSpeed() { return m_movSpeed; }
        engine::LVec3 movDirection() { return m_movDirection; }

        TPlayerTrail& trail() { return m_trail; }
    };






    
}