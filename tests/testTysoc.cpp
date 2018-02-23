
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

    auto _player = new tysoc::TPlayerEntity( engine::LVec3( 0, 3, 0 ) );
    m_world->addEntity( _player );

    m_world->setTerrain( new tysoc::TTerrain1DPatched( m_world ) );

    auto _cameraFixed = new engine::LFixedCamera3d( engine::LVec3( -4.5f, 4.7f, -5.9f ),
                                                    engine::LVec3( 0.65f, -0.38f, 0.65f ),
                                                    engine::LVec3( 0.0f, 1.0f, 0.0f ) );

     auto _cameraFPS = new engine::LFpsCamera( engine::LVec3( 1.0f, 2.0f, -1.0f ),
                                               engine::LVec3( 0.0f, 1.0f, 0.0f ) );

    m_world->addCamera( _cameraFixed, "mainCameraFixed" );
    m_world->addCamera( _cameraFPS, "cameraFPS" );

    auto _light = new engine::LLightDirectional( engine::LVec3( 0.2, 0.2, 0.2 ), engine::LVec3( 0.8, 0.8, 0.8 ),
                                                 engine::LVec3( 0.05, 0.05, 0.05 ), 0, engine::LVec3( -1, -1, -1 ) );


    //_camera->setMovVelocity( 0.1 * _player->movSpeed(), _player->movDirection() );

    m_world->addLight( _light );

    m_ui = new tysoc::TDebugUI( m_window->getGLFWwindow() );
    m_ui->init( m_world );

    cout << "done initializing testapp" << endl;
}




int main()
{
    auto _app = new TestApp();

    _app->run();

    delete _app;

    return 0;
}
