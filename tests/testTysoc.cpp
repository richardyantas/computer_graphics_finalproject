
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
    m_world->addEntity( new tysoc::TPlayerEntity( engine::LVec3( 0, 5, 0 ) ) );
    m_world->setTerrain( new tysoc::TTerrain1DPatched( m_world ) );
    m_world->addCamera( new engine::LFixedCamera3d( engine::LVec3( 10.0f, 0.0f, 10.0f ),
                                                    engine::LVec3( -10.0f, 0.0f, -10.0f ),
                                                    engine::LVec3( 0.0f, 1.0f, 0.0f ) ),
                        "mainCamera" );
    // m_world->addCamera( new engine::LFpsCamera( engine::LVec3( 0.0f, 0.0f, 0.0f ),
    //                                             engine::LVec3( 0.0f, 1.0f, 0.0f ) ),
    //                     "mainCamera" );

    cout << "done initializing testapp" << endl;
}




int main()
{
    auto _app = new TestApp();

    _app->run();

    delete _app;

    return 0;
}
