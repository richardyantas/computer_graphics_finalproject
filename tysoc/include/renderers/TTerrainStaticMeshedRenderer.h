
#pragma once

#include <terrain/TTerrainStaticMeshed.h>

#include <LICamera.h>
#include <LLightDirectional.h>
#include <LShadowMap.h>
#include <shaders/LShaderManager.h>
#include <shaders/LShaderBasic3d.h>
#include <shaders/LShaderShadowMap.h>
#include <shaders/LShaderEntitiesLighting.h>
#include <shaders/LShaderEntitiesLightingShadows.h>


using namespace std;

namespace tysoc
{


    class TTerrainStaticMeshedRenderer
    {

        private :

        bool m_useShadowMapping;
        engine::LShadowMap* m_shadowMapRef;
        vector< engine::LMesh* > m_renderables;

        TWorld* m_worldRef;
        engine::LICamera* m_cameraRef;
        engine::LLightDirectional* m_lightRef;

        public :

        TTerrainStaticMeshedRenderer();
        ~TTerrainStaticMeshedRenderer();

        void prepare( TWorld* pWorld, bool useShadowMapping, engine::LShadowMap* pShadowMapRef );
        void render( bool drawToShadowMap = false );
        void clean();
    };



}