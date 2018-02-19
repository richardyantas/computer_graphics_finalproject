
#include <TApp.h>
#include <TPlayerEntity.h>
#include <TTerrain1DPatched.h>

#include <LFixedCamera3d.h>
#include <LFpsCamera.h>

using namespace std;

class TestApp : public tysoc::TApp
{

    public :

    TestApp() : tysoc::TApp()
    {
        init();
    }

    void init() override;

};

void TestApp::init()
{
    cout << "initializing testapp" << endl;
    m_world = new tysoc::TWorld();

    auto _player = new tysoc::TPlayerEntity( engine::LVec3( 5, 15, 0 ) );
    m_world->addEntity( _player );

    m_world->setTerrain( new tysoc::TTerrain1DPatched( m_world ) );

    auto _camera = new engine::LFixedCamera3d( engine::LVec3( 22.8f, 17.8f, 22.1f ),
                                               engine::LVec3( -0.44f, -0.33f, -0.83f ),
                                               engine::LVec3( 0.0f, 1.0f, 0.0f ) );

    //auto _camera = new engine::LFpsCamera( engine::LVec3( 10.0f, 0.0f, 10.0f ),
    //                                       engine::LVec3( 0.0f, 1.0f, 0.0f ) );

    m_world->addCamera( _camera, "mainCamera" );


    _camera->setMovVelocity( 0.1 * _player->movSpeed(), _player->movDirection() );


    cout << "done initializing testapp" << endl;
}




int main()
{
    auto _app = new TestApp();

    _app->run();

    delete _app;

    return 0;
}
