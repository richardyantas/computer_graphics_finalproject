
#include "TEntitiesRenderer.h"

#include <TGraphicsComponent.h>
#include <TBasicGraphicsComponent.h>
#include <TPrimitiveGraphicsComponent.h>

#include <iostream>

using namespace std;

namespace tysoc
{

    TEntitiesRenderer::TEntitiesRenderer()
    {
        m_worldRef = NULL;
        m_cameraRef = NULL;

        for ( int q = 0; q < RENDERABLE_MAX_TYPE; q++ )
        {
            m_renderables[ q ] = vector< engine::LIRenderable* >();
        }
    }

    TEntitiesRenderer::~TEntitiesRenderer()
    {
        m_worldRef = NULL;
        m_cameraRef = NULL;
    }

    void TEntitiesRenderer::prepare( TWorld* pWorld )
    {
        m_worldRef = pWorld;
        m_cameraRef = pWorld->getCurrentCamera();
        
        // TODO: Change this part to a more general-clean way

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

            _graphicsComponent = _entity->getComponent< TPrimitiveGraphicsComponent >();
            if ( _graphicsComponent != NULL )
            {
                auto _renderable = _graphicsComponent->getRenderable();

                m_renderables[ _renderable->getType() ].push_back( _renderable );
            }            
        }
    }

    void TEntitiesRenderer::render()
    {
        assert( m_worldRef != NULL );

        auto _dirLights = m_worldRef->getLights< engine::LLightDirectional >();

        assert( _dirLights.size() > 0 );

        // For now just test a single directional light
        auto _light = _dirLights[0];

        for ( int q = 0; q < RENDERABLE_MAX_TYPE; q++ )
        {
            switch ( q ) 
            {
                case RENDERABLE_TYPE_MESH :

                    auto _shader = ( engine::LShaderEntitiesLighting* ) engine::LShaderManager::INSTANCE->programObjs["lighting_entities"];

                    _shader->bind();
                    _shader->setProjectionMatrix( m_cameraRef->getProjectionMatrix() );
                    _shader->setViewMatrix( m_cameraRef->getViewMatrix() );

                    _shader->setGlobalAmbientLight( m_worldRef->getGlobalAmbientLight() );
                    _shader->setLightDirectional( _light );
                    _shader->setViewPosition( m_cameraRef->getPosition() );

                    for ( int i = 0; i < m_renderables[q].size(); i++ )
                    {
                        // Render mesh
                        auto _mesh = reinterpret_cast< engine::LMesh* >( m_renderables[q][i] );

                        _shader->setModelMatrix( _mesh->getModelMatrix() );
                        _shader->setMaterial( _mesh->getMaterial() );
                        
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

        m_worldRef = NULL;
        m_cameraRef = NULL;
    }

}