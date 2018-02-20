
#include <TTerrain1DPatchedRenderer.h>

using namespace std;

namespace tysoc
{

    TTerrain1DPatchedRenderer::TTerrain1DPatchedRenderer()
    {
        m_cameraRef = NULL;
    }


    TTerrain1DPatchedRenderer::~TTerrain1DPatchedRenderer()
    {
        m_cameraRef = NULL;
        m_renderables.clear();
    }


    void TTerrain1DPatchedRenderer::prepare( TWorld* pWorld )
    {
        m_cameraRef = pWorld->getCurrentCamera();

        if ( pWorld->getTerrain() == NULL )
        {
            return;
        }

        if ( pWorld->getTerrain()->type == TTerrain1DPatched::getStaticType() )
        {
            auto _terrain1DPatched = reinterpret_cast< TTerrain1DPatched* >( pWorld->getTerrain() );
            auto _patches = _terrain1DPatched->getPatches();

            for ( auto _patch : _patches )
            {
                vector< engine::LMesh* > _meshes = _patch->getVoxelsGraphics();
                for ( auto _mesh : _meshes )
                {
                    m_renderables.push_back( _mesh );
                }
            }
        }
    }


    void TTerrain1DPatchedRenderer::render()
    {
        auto _shader = ( engine::LShaderBasic3d* ) engine::LShaderManager::INSTANCE->programObjs[ "basic3d" ];
        _shader->bind();

        _shader->setProjectionMatrix( m_cameraRef->getProjectionMatrix() );
        _shader->setViewMatrix( m_cameraRef->getViewMatrix() );

        for ( auto _mesh : m_renderables )
        {
            _shader->setModelMatrix( _mesh->getModelMatrix() );
            _shader->setColor( _mesh->getMaterial()->getColor() );

            _mesh->render();
        }

        _shader->unbind();
    }


    void TTerrain1DPatchedRenderer::clean()
    {
        m_renderables.clear();
    }

}