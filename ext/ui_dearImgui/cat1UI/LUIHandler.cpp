
#include "LUIHandler.h"

#include <GLFW/glfw3.h>

using namespace std;


namespace cat1UI
{


    LUIHandler* LUIHandler::INSTANCE = NULL;


    LUIHandler::LUIHandler( GLFWwindow* pWindow )
    {
        m_glfwWindow = pWindow;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init( m_glfwWindow, false );
        ImGui::StyleColorsDark();
    }

    LUIHandler* LUIHandler::create( GLFWwindow* pWindow )
    {
        if ( LUIHandler::INSTANCE != NULL )
        {
            delete LUIHandler::INSTANCE;
        }

        LUIHandler::INSTANCE = new LUIHandler( pWindow );

        return LUIHandler::INSTANCE;
    }

    void LUIHandler::release()
    {
        if ( LUIHandler::INSTANCE != NULL )
        {
            delete LUIHandler::INSTANCE;
            LUIHandler::INSTANCE = NULL;
        }

        ImGui_ImplGlfwGL3_Shutdown();
        ImGui::DestroyContext();
    }

    LUIHandler::~LUIHandler()
    {
        for ( auto _it : m_windows )
        {
            delete _it.second;
        }

        m_windows.clear();
    }

    void LUIHandler::addWindow( LUIWindow* pWindow )
    {
        if ( m_windows.find( pWindow->getName() ) != m_windows.end() )
        {
            cout << "warning!, there is already a window with id: " 
                 << pWindow->getName() << ", so not adding it." << endl;
            return;
        }

        m_windows[ pWindow->getName() ] = pWindow;
    }

    void LUIHandler::render()
    {
        ImGui_ImplGlfwGL3_NewFrame();

        for ( auto _it : m_windows )
        {
            if ( !_it.second->isActive() )
            {
                continue;
            }
            
            _it.second->render();
        }

        int _ww, _wh;
        glfwGetFramebufferSize( m_glfwWindow, &_ww, &_wh );

        glViewport( 0, 0, _ww, _wh );
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData( ImGui::GetDrawData() );
    }
}