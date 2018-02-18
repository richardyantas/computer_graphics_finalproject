
#include <TApp.h>


namespace tysoc
{


    TApp::TApp()
    {
        m_window = new engine::LWindow();
        engine::LInputHandler::create( m_window );
        engine::LShaderManager::create();

        m_masterRenderer = new TMasterRenderer();

        m_tBef = 0.0f;
        m_tNow = 0.0f;
        m_tDelta = 0.0f;

        m_world = NULL;

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

        engine::LInputHandler::release();
        engine::LShaderManager::release();
    }
    
    void TApp::init()
    {
        
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

            m_world->update( m_tDelta );

            m_masterRenderer->prepare( m_world );
            m_masterRenderer->render();
            m_masterRenderer->clean();

            m_window->swapBuffers();
        }

    }
}