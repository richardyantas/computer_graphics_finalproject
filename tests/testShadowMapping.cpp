
#include <LWindow.h>
#include <LInputHandler.h>
#include <LShaderManager.h>
#include <LShadowMap.h>
#include <LLightDirectional.h>
#include <LFpsCamera.h>
#include <LMeshBuilder.h>
#include <LShaderBasic3d.h>
#include <LShaderEntitiesLightingShadows.h>
#include <LShaderShadowMap.h>
#include <LShaderFramebufferScreenRender.h>
#include <LFrameBuffer.h>

#include <LUIHandler.h>

#include <iostream>

using namespace std;


int main()
{
    auto _window = new engine::LWindow();

    engine::LInputHandler::create( _window );
    engine::LShaderManager::create();

    auto _uiHandler = cat1UI::LUIHandler::create( _window->getGLFWwindow() );

    auto _uiWindow1 = new cat1UI::LUIWindow( "uiWindow1" );
    _uiWindow1->addTextWidget( 0, "textSample", "foooo" );
    _uiWindow1->addButtonWidget( 1, "buttonSample", "pressMe" );
    _uiWindow1->addSliderWidget( 2, "sliderSample", 0, 1, 0.5, "fuuuuun" );
    _uiWindow1->addCheckboxWidget( 3, "checkboxSample", false, "baaar" );

    _uiHandler->addWindow( _uiWindow1 );

    auto _camera = new engine::LFpsCamera( engine::LVec3( -1.0f, 1.0f, 0.0f ),
                                           engine::LVec3( 0.0f, 1.0f, 0.0f ) );


    auto _light = new engine::LLightDirectional( engine::LVec3( 0.1, 0.1, 0.1 ), engine::LVec3( 0.8, 0.8, 0.8 ),
                                                 engine::LVec3( 0.05, 0.05, 0.05 ), 0, engine::LVec3( -1, -1, -1 ) );

    auto _sphere = engine::LMeshBuilder::createSphere( 1.0f, 15, 15 );
    _sphere->pos.x = 1;
    _sphere->pos.y = 1;
    _sphere->pos.z = 1;

    auto _plane = engine::LMeshBuilder::createPlane( 10, 10 );

    auto _shadowmap = new engine::LShadowMap();

    GLfloat _quadPositions[] = {
        -1.0f,  1.0f,  
        -1.0f, -1.0f,  
         1.0f, -1.0f,
        -1.0f,  1.0f,  
         1.0f, -1.0f,  
         1.0f,  1.0f  
    };

    GLfloat _quadTexCoords[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    auto _quadVAO = new engine::LVertexArray();
    auto _quadPositionsBuffer = new engine::LVertexBuffer();
    auto _quadTexCoordsBuffer = new engine::LVertexBuffer();

    _quadPositionsBuffer->setData( sizeof( _quadPositions ), 2, _quadPositions );
    _quadTexCoordsBuffer->setData( sizeof( _quadTexCoords ), 2, _quadTexCoords );

    _quadVAO->addBuffer( _quadPositionsBuffer, 0 );
    _quadVAO->addBuffer( _quadTexCoordsBuffer, 1 );

    while ( _window->isActive() )
    {
        _window->pollEvents();
        _window->clear();

        _camera->update( 0.02 );

        {
            _shadowmap->bind();

            auto _shader = ( engine::LShaderShadowMap* ) engine::LShaderManager::INSTANCE->programObjs["shadow_mapping"];

            _shader->bind();

            _shadowmap->setupLightDirectional( _light );

            _shader->setLightSpaceViewMatrix( _shadowmap->getLightSpaceViewMatrix() );
            _shader->setLightSpaceProjectionMatrix( _shadowmap->getLightSpaceProjectionMatrix() );

            {
                _shader->setModelMatrix( _sphere->getModelMatrix() );
                _sphere->render();

                _shader->setModelMatrix( _plane->getModelMatrix() );
                _plane->render();
            }

            _shader->unbind();

            _shadowmap->unbind();
        }
        
        // test shadow mapping

        {
            auto _shader = ( engine::LShaderEntitiesLightingShadows* ) engine::LShaderManager::INSTANCE->programObjs["lighting_entities_shadows"];

            _shader->bind();

            glBindTexture( GL_TEXTURE_2D, _shadowmap->getDepthTexture() );

            _shader->setLightDirectional( _light );
            _shader->setViewMatrix( _camera->getViewMatrix() );
            _shader->setProjectionMatrix( _camera->getProjectionMatrix() );
            _shader->setViewPosition( _camera->getPosition() );
            _shader->setGlobalAmbientLight( engine::LVec3( 0.2, 0.2, 0.2 ) );
            _shader->setLightSpaceViewMatrix( _shadowmap->getLightSpaceViewMatrix() );
            _shader->setLightSpaceProjectionMatrix( _shadowmap->getLightSpaceProjectionMatrix() );
            _shader->setLightPosition( _shadowmap->getLightPosition() );

            {
                _shader->setModelMatrix( _sphere->getModelMatrix() );
                _shader->setMaterial( _sphere->getMaterial() );

                _sphere->render();

                _shader->setModelMatrix( _plane->getModelMatrix() );
                _shader->setMaterial( _plane->getMaterial() );

                _plane->render();
            }


            _shader->unbind();
        }

        // draw shadowmap to bottom-left corner

        glViewport( 0, _window->height() - 200, 200, 200 );

        glDisable( GL_DEPTH_TEST );

        auto _shaderFB = ( engine::LShaderFramebufferScreenRender* ) engine::LShaderManager::INSTANCE->programObjs["pp_framebuffer_screenrender_channel"];
        _shaderFB->bind();
        _shaderFB->setTextureSamplingChannel( 0 );

        {
            glBindTexture( GL_TEXTURE_2D, _shadowmap->getDepthTexture() );

            _quadVAO->bind();
            glDrawArrays( GL_TRIANGLES, 0, 6 );
            _quadVAO->unbind();
        }
            

        _shaderFB->unbind();

        glEnable( GL_DEPTH_TEST );

        glViewport( 0, 0, _window->width(), _window->height() );

        _uiHandler->render();

        _window->swapBuffers();
    }

    cat1UI::LUIHandler::release();

    delete _camera;
    delete _window;
    delete _sphere;

    return 0;
}