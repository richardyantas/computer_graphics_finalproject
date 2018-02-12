
#include <TTerrainRenderer.h>

#include <iostream>

using namespace std;


namespace tysoc
{


    TTerrainRenderer::TTerrainRenderer()
    {
        m_terrain1DPatchedRenderer = new TTerrain1DPatchedRenderer();
    }

    TTerrainRenderer::~TTerrainRenderer()
    {
        delete m_terrain1DPatchedRenderer;
    }

    void TTerrainRenderer::prepare( TWorld* pWorld )
    {
        m_terrain1DPatchedRenderer->prepare( pWorld );
    }

    void TTerrainRenderer::render()
    {
        m_terrain1DPatchedRenderer->render();
    }

    void TTerrainRenderer::clean()
    {
        m_terrain1DPatchedRenderer->clean();
    }

}