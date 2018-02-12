
#pragma once

#include "TWorld.h"
#include <string>

using namespace std;

#define TERRAIN1D_DEFAULT_START     engine::LVec3( 0, 0, 0 )
#define TERRAIN1D_DEFAULT_DIRECTION engine::LVec3( 1, 0, 0 )
#define TERRAIN1D_DEFAULT_UP        engine::LVec3( 0, 1, 0 )

namespace tysoc
{

    class TWorld;

    /**
    * @brief : terrain created along a ...
    *          single direction. Useful for runners :D
    */
    class TTerrain1D
    {

        protected :

        TWorld* m_world;
        
        float m_current1DPos;

        engine::LVec3 m_start;
        engine::LVec3 m_direction;
        engine::LVec3 m_up;

        public :

        string type;

        TTerrain1D( TWorld* pWorld,
                    engine::LVec3 start       = TERRAIN1D_DEFAULT_START,
                    engine::LVec3 direction   = TERRAIN1D_DEFAULT_DIRECTION,
                    engine::LVec3 up          = TERRAIN1D_DEFAULT_UP );

        ~TTerrain1D();

        static string getStaticType() { return string( "base" ); }

        virtual void update( float dt );

    };




}