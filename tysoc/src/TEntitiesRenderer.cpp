
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
        m_lightRef = NULL;
        m_useShadowMapping = false;
        m_shadowMapRef = NULL;

        for ( int q = 0; q < RENDERABLE_MAX_TYPE; q++ )
        {
            m_renderables[ q ] = vector< engine::LIRenderable* >();
        }
    }

    TEntitiesRenderer::~TEntitiesRenderer()
    {
        m_worldRef = NULL;
        m_cameraRef = NULL;
        m_lightRef = NULL;
        m_shadowMapRef = NULL;
    }

    void TEntitiesRenderer::prepare( TWorld* pWorld, bool useShadowMapping, engine::LShadowMap* pShadowMapRef )
    {
        m_worldRef = pWorld;
        m_cameraRef = pWorld->getCurrentCamera();

        m_useShadowMapping = useShadowMapping;
        m_shadowMapRef = pShadowMapRef;

        auto _lights = pWorld->getLights< engine::LLightDirectional >();
        if ( _lights.size() > 0 )
        {
            m_lightRef = _lights[0];
        }

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

    void TEntitiesRenderer::render( bool drawToShadowMap )
    {
        // TODO: Refactor this part. Should keep meshes of distinct types in ...
        // different buffers

        if ( m_useShadowMapping )
        {
            if ( drawToShadowMap )
            {
                // first render pass

                for ( int q = 0; q < RENDERABLE_MAX_TYPE; q++ )
                {
                    switch ( q ) 
                    {
                        case RENDERABLE_TYPE_MESH :

                            auto _shader = ( engine::LShaderShadowMap* ) engine::LShaderManager::INSTANCE->programObjs[ "shadow_mapping" ];

                            _shader->bind();
                            _shader->setLightSpaceViewMatrix( m_shadowMapRef->getLightSpaceViewMatrix() );
                            _shader->setLightSpaceProjectionMatrix( m_shadowMapRef->getLightSpaceProjectionMatrix() );

                            for ( int i = 0; i < m_renderables[q].size(); i++ )
                            {
                                // Render mesh
                                auto _mesh = reinterpret_cast< engine::LMesh* >( m_renderables[q][i] );

                                _shader->setModelMatrix( _mesh->getModelMatrix() );
                                _mesh->render();
                            }

                            _shader->unbind();

                        break;
                    }
                }
            }
            else
            {
                // second render pass

                for ( int q = 0; q < RENDERABLE_MAX_TYPE; q++ )
                {
                    switch ( q ) 
                    {
                        case RENDERABLE_TYPE_MESH :

                            auto _shader = ( engine::LShaderEntitiesLightingShadows* ) engine::LShaderManager::INSTANCE->programObjs[ "lighting_entities_shadows" ];

                            _shader->bind();
                            glBindTexture( GL_TEXTURE_2D, m_shadowMapRef->getDepthTexture() );

                            _shader->setLightDirectional( m_lightRef );
                            _shader->setViewMatrix( m_cameraRef->getViewMatrix() );
                            _shader->setProjectionMatrix( m_cameraRef->getProjectionMatrix() );
                            _shader->setViewPosition( m_cameraRef->getPosition() );
                            _shader->setGlobalAmbientLight( m_worldRef->getGlobalAmbientLight() );
                            _shader->setLightSpaceViewMatrix( m_shadowMapRef->getLightSpaceViewMatrix() );
                            _shader->setLightSpaceProjectionMatrix( m_shadowMapRef->getLightSpaceProjectionMatrix() );
                            _shader->setLightPosition( m_shadowMapRef->getLightPosition() );

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
        }
        else
        {
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
                        _shader->setLightDirectional( m_lightRef );
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