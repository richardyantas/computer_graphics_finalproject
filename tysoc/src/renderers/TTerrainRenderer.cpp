
#include <renderers/TTerrainRenderer.h>

#include <iostream>

using namespace std;


namespace tysoc
{


    TTerrainRenderer::TTerrainRenderer()
    {
        m_useShadowMapping = false;
        m_shadowMapRef = NULL;

        m_patched1dRenderer = new TTerrain1DPatchedRenderer();
        m_staticMeshedRenderer = new TTerrainStaticMeshedRenderer();
    }

    TTerrainRenderer::~TTerrainRenderer()
    {
        m_shadowMapRef = NULL;

        delete m_patched1dRenderer;
        delete m_staticMeshedRenderer;
    }

    void TTerrainRenderer::prepare( TWorld* pWorld, bool useShadowMapping, engine::LShadowMap* pShadowMapRef )
    {
        m_useShadowMapping = useShadowMapping;
        m_shadowMapRef = pShadowMapRef;

        m_patched1dRenderer->prepare( pWorld, useShadowMapping, pShadowMapRef );
        m_staticMeshedRenderer->prepare( pWorld, useShadowMapping, pShadowMapRef );
    }

    void TTerrainRenderer::render( bool drawToShadowMap )
    {
        if ( m_useShadowMapping )
        {
            m_patched1dRenderer->render( drawToShadowMap );
            m_staticMeshedRenderer->render( drawToShadowMap );
        }
        else
        {
            m_patched1dRenderer->render( false );
            m_staticMeshedRenderer->render( false );
        }
    }

    void TTerrainRenderer::clean()
    {
        m_useShadowMapping = false;
        m_shadowMapRef = NULL;

        m_patched1dRenderer->clean();
        m_staticMeshedRenderer->clean();
    }

}