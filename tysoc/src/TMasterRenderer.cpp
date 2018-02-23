
#include <TMasterRenderer.h>



namespace tysoc
{

    // TODO: Change the shadowmapping render stages into a ...
    // cleaner version. It now uses too many flags to my view

    TMasterRenderer::TMasterRenderer()
    {
        m_terrainRenderer = new TTerrainRenderer();
        m_entitiesRenderer = new TEntitiesRenderer();

        m_drawAsWireframe = false;
        m_drawShadows = true;
        m_shadowMap = new engine::LShadowMap();
        m_lightRef = NULL;
    }

    TMasterRenderer::~TMasterRenderer()
    {
        m_lightRef = NULL;
        delete m_shadowMap;
        delete m_terrainRenderer;
        delete m_entitiesRenderer;
    }


    void TMasterRenderer::prepare( TWorld* pWorld )
    {
        auto _lights = pWorld->getLights< engine::LLightDirectional >();
        if ( _lights.size() > 0 )
        {
            m_lightRef = _lights[0];
        }

        m_terrainRenderer->prepare( pWorld, m_drawShadows, m_shadowMap );
        m_entitiesRenderer->prepare( pWorld, m_drawShadows, m_shadowMap );
    }

    void TMasterRenderer::render()
    {
        // Generate shadowmap if necessary

        if ( m_drawShadows )
        {
            // First pass - render to shadowmap
            {
                m_shadowMap->bind();
                
                m_shadowMap->setupLightDirectional( m_lightRef );

                m_terrainRenderer->render( true );
                m_entitiesRenderer->render( true );

                m_shadowMap->unbind();
            }
            
            // Second pass - render with shadowmap
            {
                // TODO: Modify this in case texturing is supported
                glBindTexture( GL_TEXTURE_2D, m_shadowMap->getDepthTexture() );

                m_terrainRenderer->render( false );
                m_entitiesRenderer->render( false );

                glBindTexture( GL_TEXTURE_2D, 0 );
            }
        }
        else
        {
            // Render with single pass if shadows are not required

            if ( m_drawAsWireframe )
            {
                glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
            }

            m_terrainRenderer->render();
            m_entitiesRenderer->render();

            if ( m_drawAsWireframe )
            {
                glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
            }
        }
    }

    void TMasterRenderer::clean()
    {
        m_terrainRenderer->clean();
        m_entitiesRenderer->clean();
    }

}