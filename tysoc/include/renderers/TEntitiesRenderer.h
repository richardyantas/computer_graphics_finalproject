
#pragma once

#include <LMesh.h>
#include <LShadowMap.h>
#include <LLightDirectional.h>
#include <shaders/LShaderManager.h>
#include <shaders/LShaderBasic3d.h>
#include <shaders/LShaderShadowMap.h>
#include <shaders/LShaderEntitiesLighting.h>
#include <shaders/LShaderEntitiesLightingShadows.h>

#include <TWorld.h>
#include <TEntity.h>

#include <vector>

using namespace std;

namespace tysoc
{



    class TEntitiesRenderer
    {

        private :


        bool m_useShadowMapping;
        engine::LShadowMap* m_shadowMapRef;
        vector< engine::LIRenderable* > m_renderables[ RENDERABLE_MAX_TYPE ];

        TWorld* m_worldRef;
        engine::LICamera* m_cameraRef;
        engine::LLightDirectional* m_lightRef;

        public :

        TEntitiesRenderer();
        ~TEntitiesRenderer();

        void prepare( TWorld* pWorld, bool useShadowMapping, engine::LShadowMap* pShadowMapRef );
        void render( bool drawToShadowMap = false );
        void clean();


    };



}