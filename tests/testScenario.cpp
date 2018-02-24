
#include <TApp.h>
#include <scenarios/TBaseScenario.h>

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
    m_world = new tysoc::TBaseScenario();

    m_ui = new tysoc::TDebugUI( m_window->getGLFWwindow() );
    m_ui->init( reinterpret_cast< tysoc::TBaseScenario* >( m_world ) );

    cout << "done initializing testapp" << endl;
}




int main()
{
    auto _app = new TestApp();

    _app->run();

    delete _app;

    return 0;
}
