
#include "TEntitiesRenderer.h"

#include <TGraphicsComponent.h>
#include <TBasicGraphicsComponent.h>

#include <iostream>

using namespace std;

namespace tysoc
{

    TEntitiesRenderer::TEntitiesRenderer()
    {
        m_cameraRef = NULL;

        for ( int q = 0; q < RENDERABLE_MAX_TYPE; q++ )
        {
            m_renderables[ q ] = vector< engine::LIRenderable* >();
        }
    }

    TEntitiesRenderer::~TEntitiesRenderer()
    {
        m_cameraRef = NULL;
    }

    void TEntitiesRenderer::prepare( TWorld* pWorld )
    {
        m_cameraRef = pWorld->getCurrentCamera();

        auto _entities = pWorld->getEntities();
        for ( TEntity* _entity : _entities )
        {
            auto _graphicsComponent = _entity->getComponent< TGraphicsComponent >();

            if ( _graphicsComponent != NULL )
            {
                auto _renderable = _graphicsComponent->getRenderable();

                m_renderables[ _renderable->getType() ].push_back( _renderable );
            }

            _graphicsComponent = _entity->getComponent< TBasicGraphicsComponent >();
            if ( _graphicsComponent != NULL )
            {
                auto _renderable = _graphicsComponent->getRenderable();

                m_renderables[ _renderable->getType() ].push_back( _renderable );
            }            
        }
    }

    void TEntitiesRenderer::render()
    {
        for ( int q = 0; q < RENDERABLE_MAX_TYPE; q++ )
        {
            switch ( q ) 
            {
                case RENDERABLE_TYPE_MESH :

                    auto _shader = ( engine::LShaderBasic3d* ) engine::LShaderManager::INSTANCE->programObjs["basic3d"];

                    _shader->bind();
                    _shader->setProjectionMatrix( m_cameraRef->getProjectionMatrix() );
                    _shader->setViewMatrix( m_cameraRef->getViewMatrix() );

                    for ( int i = 0; i < m_renderables[q].size(); i++ )
                    {
                        // Render mesh
                        auto _mesh = reinterpret_cast< engine::LMesh* >( m_renderables[q][i] );

                        _shader->setModelMatrix( _mesh->getModelMatrix() );
                        _shader->setColor( _mesh->getMaterial()->getColor() );
                        
                        _mesh->render();
                    }

                    _shader->unbind();

                break;
            }
        }
    }

    void TEntitiesRenderer::clean()
    {
        for ( int q = 0; q < RENDERABLE_MAX_TYPE; q++ )
        {
            m_renderables[q].clear();
        }
    }

}