
#pragma once

#include "TCommon.h"
#include "TEntity.h"

using namespace std;

namespace tysoc
{



    class TPhysicsComponent : public TComponent
    {

        protected :

        

        public :

        TPhysicsComponent( TEntity* pParent );
        ~TPhysicsComponent();

        static string getStaticType() { return string( "physics" ); }

        virtual void update( float dt ) = 0;

        virtual void applyImpulse( const btVector3& impulse );

    };



}