
#pragma once

#include "TPhysicsComponent.h"


using namespace std;

namespace tysoc
{


    class TBasicPhysicsComponent : public TPhysicsComponent
    {


        private :

        btRigidBody* m_rBody;

        public :

        TBasicPhysicsComponent( TEntity* pParent );
        TBasicPhysicsComponent( TEntity* pParent, btRigidBody* pRigidBody );
        ~TBasicPhysicsComponent();

        static string getStaticType() { return string( "basePhysics" ); }

        void update( float dt ) override;

        btRigidBody* getRigidBody() { return m_rBody; }

    };






}






