
#include <LWindow.h>
#include <LInputHandler.h>
#include <LShaderManager.h>
#include <LFpsCamera.h>
#include <LMeshBuilder.h>
#include <LShaderBasic3d.h>
#include <LShaderFramebufferScreenRender.h>
#include <LFrameBuffer.h>

#include <iostream>

using namespace std;


int main()
{
    auto _window = new engine::LWindow();

    engine::LInputHandler::create( _window );
    engine::LShaderManager::create();

    auto _camera = new engine::LFpsCamera( engine::LVec3( -1.0f, 1.0f, 0.0f ),
                                           engine::LVec3( 0.0f, 1.0f, 0.0f ) );


    auto _sphere = engine::LMeshBuilder::createSphere( 1.0f, 15, 15 );
    _sphere->drawAsWireframe = true;

    auto _frameBuffer = new engine::LFrameBuffer( GL_RGB, GL_UNSIGNED_BYTE, GL_COLOR_ATTACHMENT0, _window->width(), _window->height() );

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

        _frameBuffer->bind();

        _window->clear();

        _camera->update( 0.02 );

        auto _shader = ( engine::LShaderBasic3d* ) engine::LShaderManager::INSTANCE->programObjs["basic3d"];

        _shader->bind();

        _shader->setViewMatrix( _camera->getViewMatrix() );
        _shader->setProjectionMatrix( _camera->getProjectionMatrix() );

        {
            _shader->setModelMatrix( _sphere->getModelMatrix() );
            _shader->setColor( engine::LVec3( 0, 0, 255 ) );
            _sphere->render();
        }

        _shader->unbind();
        _frameBuffer->unbind();

        glDisable( GL_DEPTH_TEST );

        auto _shaderFB = ( engine::LShaderFramebufferScreenRender* ) engine::LShaderManager::INSTANCE->programObjs["pp_framebuffer_screenrender"];
        _shaderFB->bind();

        {
            glBindTexture( GL_TEXTURE_2D, _frameBuffer->getTex() );

            _quadVAO->bind();
            glDrawArrays( GL_TRIANGLES, 0, 6 );
            _quadVAO->unbind();
        }
            

        _shaderFB->unbind();

        glEnable( GL_DEPTH_TEST );

        _window->swapBuffers();
    }


    delete _camera;
    delete _window;
    delete _sphere;

    return 0;
}