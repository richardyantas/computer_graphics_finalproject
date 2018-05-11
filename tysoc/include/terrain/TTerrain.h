

#pragma once

#include <TWorld.h>

using namespace std;

namespace tysoc
{

    class TWorld;

    class TTerrain
    {

        protected : 

        TWorld* m_world;
        string m_type;

        public :

        TTerrain( TWorld* world );
        ~TTerrain();

        string type() { return m_type; }
        static string getStaticType() { return string( "base" ); }

        virtual void update( float dt ) = 0;
        virtual void setMaterial( const engine::LVec3& ambient,
                                  const engine::LVec3& diffuse,
                                  const engine::LVec3& specular,
                                  float shininess ) = 0;
    };



}


