
#pragma once


#include "TCommon.h"
#include "TWorld.h"
#include "TTerrain1DPatchedRenderer.h"
#include <LShadowMap.h>


namespace tysoc
{


    class TTerrainRenderer
    {

        private :

        bool m_useShadowMapping;
        engine::LShadowMap* m_shadowMapRef;
        TTerrain1DPatchedRenderer* m_terrain1DPatchedRenderer;

        public :

        TTerrainRenderer();
        ~TTerrainRenderer();

        void prepare( TWorld* pWorld, bool useShadowMapping, 
                      engine::LShadowMap* pShadowMapRef );
        void render( bool drawToShadowMap = false );
        void clean();

    };



}