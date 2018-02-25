
#pragma once

#include "TWorld.h"
#include <string>
#include <LFixedCamera3d.h>

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
        engine::LVec3 m_direction;// like front
        engine::LVec3 m_up;
        engine::LVec3 m_side;

        TAABB m_cameraRangeWorldAxes;
        TAABB m_cameraRangeMovementAxes;

        TAABB _computeRangeFromCamera( engine::LFixedCamera3d* pCamera );

        public :

        string type;

        TTerrain1D( TWorld* pWorld,
                    engine::LVec3 start       = TERRAIN1D_DEFAULT_START,
                    engine::LVec3 direction   = TERRAIN1D_DEFAULT_DIRECTION,
                    engine::LVec3 up          = TERRAIN1D_DEFAULT_UP );

        ~TTerrain1D();

        static string getStaticType() { return string( "base" ); }

        void computeBoxRangeFromCameras( const vector< engine::LFixedCamera3d* >& vCameras );

        TAABB getCameraRangeWorldAxes() { return m_cameraRangeWorldAxes; }
        TAABB getCameraRangeMovementAxes() { return m_cameraRangeMovementAxes; }

        virtual void update( float dt );
        virtual void setMaterial( const engine::LVec3& ambient,
                                  const engine::LVec3& diffuse,
                                  const engine::LVec3& specular,
                                  float shininess );
    };




}