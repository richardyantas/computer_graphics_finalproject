
#pragma once

#include "TComponent.h"
#include <LIRenderable.h>


namespace tysoc
{


    class TGraphicsComponent : public TComponent
    {

        protected :

        engine::LIRenderable* m_renderable;

        public :

        TGraphicsComponent( TEntity* parent );
        ~TGraphicsComponent();


        static string getStaticType() { return string( "igraphicsComponent" ); }
        
        void setRenderable( engine::LIRenderable* pRenderable ) { m_renderable = pRenderable; }
        engine::LIRenderable* getRenderable() { return m_renderable; }

        void update( float dt ) override;
        
    };


}