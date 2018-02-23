
#include <TApp.h>


namespace tysoc
{
    TApp* TApp::INSTANCE = NULL;

    TApp::TApp()
    {
        TApp::INSTANCE = this;

        m_window = new engine::LWindow();
        engine::LInputHandler::create( m_window );
        engine::LShaderManager::create();

        engine::LInputHandler::INSTANCE->addUserCallback( TApp::onKeyCallback );

        m_masterRenderer = new TMasterRenderer();

        m_tBef = 0.0f;
        m_tNow = 0.0f;
        m_tDelta = 0.0f;

        m_world = NULL;
        m_ui = NULL;
        init();
    }

    TApp::~TApp()
    {
        if ( m_window != NULL )
        {
            delete m_window;
            m_window = NULL;
        }

        if ( m_masterRenderer != NULL )
        {
            delete m_masterRenderer;
            m_masterRenderer = NULL;
        }

        if ( m_world != NULL )
        {
            delete m_world;
            m_world = NULL;
        }

        if ( m_ui != NULL )
        {
            delete m_ui;
            m_ui = NULL;
        }

        engine::LInputHandler::release();
        engine::LShaderManager::release();
    }
    
    void TApp::init()
    {
        // Override this
    }

    void TApp::run()
    {
        assert( m_world != NULL );

        while ( m_window->isActive() )
        {
            m_window->clear();
            m_window->pollEvents();

            m_tNow = glfwGetTime();
            m_tDelta = m_tNow - m_tBef;
            m_tDelta = ( m_tDelta > MAX_DELTA ) ? MAX_DELTA : m_tDelta;

            _customUpdate( m_tDelta );

            m_world->update( m_tDelta );

            m_masterRenderer->prepare( m_world );
            m_masterRenderer->render();
            m_masterRenderer->clean();

            if ( m_ui != NULL )
            {
                m_ui->render();
            }

            m_window->swapBuffers();
        }

    }

    void TApp::_customUpdate( float dt )
    {
        // Override this
    }

    void TApp::onKeyCallback( int key, int action )
    {
        if ( key == GLFW_KEY_I )
        {
            TApp::INSTANCE->dumpInfo();
        }
    }

    void TApp::dumpInfo()
    {
        if ( m_world != NULL )
        {
            m_world->dumpInfo();
        }
    }
}