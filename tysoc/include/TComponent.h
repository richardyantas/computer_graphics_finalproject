
#pragma once

#include "LCommon.h"
#include "TEntity.h"

using namespace std;


namespace tysoc
{

    class TEntity;

    class TComponent
    {

        protected :

        TEntity* m_parent;

        public :

        string type;
        TComponent( TEntity* pParent );
        ~TComponent();

        static string getStaticType();
        
        TEntity* getEntity() { return m_parent; }

        virtual void update( float dt );

    };


}