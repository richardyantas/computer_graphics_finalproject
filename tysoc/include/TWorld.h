
#pragma once

#include "TCommon.h"
#include "TEntity.h"
#include "TTerrain1D.h"

#include <LICamera.h>
#include <LMeshBuilder.h>
#include <LILight.h>
#include <LLightDirectional.h>
#include <LLightPoint.h>
#include <LLightSpot.h>

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

#define WORLD_DEFAULT_AMBIENT_LIGHT engine::LVec3( 0.1, 0.1, 0.1 )

namespace tysoc
{

    class TTerrain1D;
    class TTerrain1DPatched;

    class TWorld
    {

        protected :

        TVec3 m_globalAmbientLight;
        vector< engine::LILight* > m_lights;

        vector< TEntity* > m_entities;
        TTerrain1D* m_terrain;

        engine::LICamera* m_currentCamera;
        unordered_map< string, engine::LICamera* > m_cameras;

        btBroadphaseInterface* m_btBroadphase;
        btDefaultCollisionConfiguration* m_btCollisionConfiguration;
        btCollisionDispatcher* m_btCollisionDispatcher;
        btSequentialImpulseConstraintSolver* m_btSolver;
        btDiscreteDynamicsWorld* m_btWorld;


        public :


        TWorld();
        ~TWorld();


        virtual void update( float dt );

        void addEntity( TEntity* pEntity );
        vector< TEntity* > getEntities() { return m_entities; }

        void setGlobalAmbientLight( const TVec3& globalAmbientLight ) { m_globalAmbientLight = globalAmbientLight; }
        TVec3 getGlobalAmbientLight() { return m_globalAmbientLight; }

        void addLight( engine::LILight* pLight ) { m_lights.push_back( pLight ); }

        unordered_map< string, engine::LICamera* > getCameras() { return m_cameras; }

        template< class T >
        vector<T*> getLights()
        {
            auto _type = T::getStaticType();

            vector< T* > _lights;

            for ( auto _light : m_lights )
            {
                if ( _light->getType() == _type )
                {
                    _lights.push_back( ( T* ) _light );
                }
            }

            return _lights;
        }

        void addCamera( engine::LICamera* pCamera, string cameraStrId );
        void changeToCamera( string cameraStrId );
        engine::LICamera* getCurrentCamera() { return m_currentCamera; }

        void setTerrain( TTerrain1D* pTerrain ) 
        { 
            if ( m_terrain != NULL )
            {
                delete m_terrain;
            }
                
            m_terrain = pTerrain; 
        }

        btDiscreteDynamicsWorld* getBulletWorld() { return m_btWorld; }

        TTerrain1D* getTerrain() { return m_terrain; }

        virtual void dumpInfo();

    };

}