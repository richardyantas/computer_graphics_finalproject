
#include <TTerrainRenderer.h>

#include <iostream>

using namespace std;


namespace tysoc
{


    TTerrainRenderer::TTerrainRenderer()
    {
        m_terrain1DPatchedRenderer = new TTerrain1DPatchedRenderer();
        m_useShadowMapping = false;
        m_shadowMapRef = NULL;
    }

    TTerrainRenderer::~TTerrainRenderer()
    {
        m_shadowMapRef = NULL;
        delete m_terrain1DPatchedRenderer;
    }

    void TTerrainRenderer::prepare( TWorld* pWorld, bool useShadowMapping, engine::LShadowMap* pShadowMapRef )
    {
        m_useShadowMapping = useShadowMapping;
        m_shadowMapRef = pShadowMapRef;
        m_terrain1DPatchedRenderer->prepare( pWorld, useShadowMapping, pShadowMapRef );
    }

    void TTerrainRenderer::render( bool drawToShadowMap )
    {
        if ( m_useShadowMapping )
        {
            m_terrain1DPatchedRenderer->render( drawToShadowMap );
        }
        else
        {
            m_terrain1DPatchedRenderer->render( false );
        }
    }

    void TTerrainRenderer::clean()
    {
        m_useShadowMapping = false;
        m_shadowMapRef = NULL;
        m_terrain1DPatchedRenderer->clean();
    }

}