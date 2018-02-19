
#include <TMasterRenderer.h>



namespace tysoc
{

    TMasterRenderer::TMasterRenderer()
    {
        m_terrainRenderer = new TTerrainRenderer();
        m_entitiesRenderer = new TEntitiesRenderer();

        m_drawAsWireframe = true;
    }

    TMasterRenderer::~TMasterRenderer()
    {
        delete m_terrainRenderer;
        delete m_entitiesRenderer;
    }


    void TMasterRenderer::prepare( TWorld* pWorld )
    {
        m_terrainRenderer->prepare( pWorld );
        m_entitiesRenderer->prepare( pWorld );
    }

    void TMasterRenderer::render()
    {
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

    void TMasterRenderer::clean()
    {
        m_terrainRenderer->clean();
        m_entitiesRenderer->clean();
    }

}