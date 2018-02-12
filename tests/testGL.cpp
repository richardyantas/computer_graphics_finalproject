
#include <LWindow.h>
#include <LInputHandler.h>
#include <LShaderManager.h>
#include <LFpsCamera.h>
#include <LMeshBuilder.h>
#include <LShaderBasic3d.h>

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

    while ( _window->isActive() )
    {
        _window->clear();
        _window->pollEvents();

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

        _window->swapBuffers();
    }


    delete _camera;
    delete _window;
    delete _sphere;

    return 0;
}