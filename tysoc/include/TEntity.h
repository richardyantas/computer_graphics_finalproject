
#pragma once

#include "TCommon.h"
#include "TComponent.h"
#include <unordered_map>

using namespace std;

namespace tysoc
{

    class TComponent;

    class TEntity
    {

        protected :

        unordered_map< string, TComponent* > m_components;

        public :

        engine::LVec3 pos;
        glm::mat4 rotation;

        TEntity();
        TEntity( const engine::LVec3& initialPosition );

        ~TEntity();

        template< class T >
        T* getComponent()
        {
            string _type = T::getStaticType();
            auto _it = m_components.find( _type );
            if ( _it == m_components.end() )
            {
                return NULL;
            }

            return ( T* ) _it->second;
        }

        void addComponent( TComponent* pComponent );

        virtual void update( float dt );
    };




}