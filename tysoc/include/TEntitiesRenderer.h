
#pragma once

#include <LShaderBasic3d.h>
#include <LShaderManager.h>
#include <LMesh.h>

#include "TWorld.h"
#include "TEntity.h"

#include <vector>

using namespace std;

namespace tysoc
{



    class TEntitiesRenderer
    {

        private :

        vector< engine::LIRenderable* > m_renderables[ RENDERABLE_MAX_TYPE ];
        engine::LICamera* m_cameraRef;

        public :

        TEntitiesRenderer();
        ~TEntitiesRenderer();

        void prepare( TWorld* pWorld );
        void render();
        void clean();


    };



}