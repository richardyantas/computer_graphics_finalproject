
#include <renderers/TTerrainStaticMeshedRenderer.h>

using namespace std;

namespace tysoc
{

    TTerrainStaticMeshedRenderer::TTerrainStaticMeshedRenderer()
    {
        m_cameraRef = NULL;
        m_worldRef = NULL;
        m_lightRef = NULL;
        m_useShadowMapping = false;
        m_shadowMapRef = NULL;
    }

    TTerrainStaticMeshedRenderer::~TTerrainStaticMeshedRenderer()
    {
        m_worldRef = NULL;
        m_cameraRef = NULL;
        m_lightRef = NULL;
        m_shadowMapRef = NULL;
        m_renderables.clear();
    }

    void TTerrainStaticMeshedRenderer::prepare( TWorld* pWorld, bool useShadowMapping, engine::LShadowMap* pShadowMapRef )
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

        if ( pWorld->getTerrain() == NULL )
        {
            return;
        }

        if ( pWorld->getTerrain()->type() == TTerrainStaticMeshed::getStaticType() )
        {
            auto _terrainStaticMeshed = reinterpret_cast< TTerrainStaticMeshed* >( pWorld->getTerrain() );

            m_renderables.push_back( _terrainStaticMeshed->getMesh() );
        }
    }

    void TTerrainStaticMeshedRenderer::render( bool drawToShadowMap )
    {
        if ( m_useShadowMapping )
        {
            if ( drawToShadowMap )
            {
                // first render pass

                auto _shader = ( engine::LShaderShadowMap* ) engine::LShaderManager::INSTANCE->programObjs[ "shadow_mapping" ];
                
                _shader->bind();
                _shader->setLightSpaceViewMatrix( m_shadowMapRef->getLightSpaceViewMatrix() );
                _shader->setLightSpaceProjectionMatrix( m_shadowMapRef->getLightSpaceProjectionMatrix() );

                for ( auto _mesh : m_renderables )
                {
                    _shader->setModelMatrix( _mesh->getModelMatrix() );
                    _mesh->render();
                }

                _shader->unbind();
                
            }
            else
            {
                // second render pass

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

                for ( auto _mesh : m_renderables )
                {
                    _shader->setModelMatrix( _mesh->getModelMatrix() );
                    _shader->setMaterial( _mesh->getMaterial() );

                    _mesh->render();
                }

                _shader->unbind();
            }
        }
        else
        {
            auto _shader = ( engine::LShaderEntitiesLighting* ) engine::LShaderManager::INSTANCE->programObjs["lighting_entities"];
            _shader->bind();

            _shader->setProjectionMatrix( m_cameraRef->getProjectionMatrix() );
            _shader->setViewMatrix( m_cameraRef->getViewMatrix() );
            _shader->setGlobalAmbientLight( m_worldRef->getGlobalAmbientLight() );
            _shader->setLightDirectional( m_lightRef );
            _shader->setViewPosition( m_cameraRef->getPosition() );

            for ( auto _mesh : m_renderables )
            {
                _shader->setModelMatrix( _mesh->getModelMatrix() );
                _shader->setMaterial( _mesh->getMaterial() );

                // cout << "_mesh.pos: " << _mesh->pos.toString() << endl;

                _mesh->render();
            }

            _shader->unbind();
        }
    }

    void TTerrainStaticMeshedRenderer::clean()
    {
        m_worldRef = NULL;
        m_cameraRef = NULL;
        m_lightRef = NULL;
        m_useShadowMapping = false;
        m_shadowMapRef = NULL;
        m_renderables.clear();
    }




}