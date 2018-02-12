
#pragma once

#include "TCommon.h"
#include "TEntity.h"
#include "TTerrain1D.h"

#include <LICamera.h>
#include <LMeshBuilder.h>

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

namespace tysoc
{

    class TTerrain1D;
    class TTerrain1DPatched;

    class TWorld
    {

        private :

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


        void update( float dt );

        void addEntity( TEntity* pEntity );
        vector< TEntity* > getEntities() { return m_entities; }

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

    };

}