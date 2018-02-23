
#pragma once

#include "TWorld.h"
#include "TTerrain1DPatched.h"
#include <LICamera.h>
#include <LLightDirectional.h>
#include <LMesh.h>
#include <LShadowMap.h>
#include <shaders/LShaderManager.h>
#include <shaders/LShaderBasic3d.h>
#include <shaders/LShaderShadowMap.h>
#include <shaders/LShaderTerrain1DVoxelsLighting.h>
#include <shaders/LShaderTerrain1DVoxelsLightingShadows.h>

namespace tysoc
{



    class TTerrain1DPatchedRenderer
    {

        private :

        bool m_useShadowMapping;
        engine::LShadowMap* m_shadowMapRef;
        vector< engine::LMesh* > m_renderables;

        TWorld* m_worldRef;
        engine::LICamera* m_cameraRef;
        engine::LLightDirectional* m_lightRef;

        public :

        TTerrain1DPatchedRenderer();
        ~TTerrain1DPatchedRenderer();

        void prepare( TWorld* pWorld, bool useShadowMapping, engine::LShadowMap* pShadowMapRef );
        void render( bool drawToShadowMap = false );
        void clean();


    };





}