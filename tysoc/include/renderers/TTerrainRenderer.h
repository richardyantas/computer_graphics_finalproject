
#pragma once


#include "TCommon.h"
#include "TWorld.h"
#include <renderers/TTerrainStaticMeshedRenderer.h>
#include <renderers/TTerrain1DPatchedRenderer.h>
#include <LShadowMap.h>


namespace tysoc
{


    class TTerrainRenderer
    {

        private :

        bool m_useShadowMapping;
        engine::LShadowMap* m_shadowMapRef;

        TTerrain1DPatchedRenderer* m_patched1dRenderer;
        TTerrainStaticMeshedRenderer* m_staticMeshedRenderer;

        public :

        TTerrainRenderer();
        ~TTerrainRenderer();

        void prepare( TWorld* pWorld, bool useShadowMapping, 
                      engine::LShadowMap* pShadowMapRef );
        void render( bool drawToShadowMap = false );
        void clean();

    };



}