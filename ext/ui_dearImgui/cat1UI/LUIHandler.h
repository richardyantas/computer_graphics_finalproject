
#pragma once

#include "LUIWindow.h"


using namespace std;


namespace cat1UI
{

    class LUIHandler
    {

        private :

        GLFWwindow* m_glfwWindow;

        unordered_map< string, LUIWindow* > m_windows;

        LUIHandler( GLFWwindow* pWindow );

        public :

        static LUIHandler* INSTANCE;
        static LUIHandler* create( GLFWwindow* pWindow );
        static void release();

        ~LUIHandler();

        void addWindow( LUIWindow* pWindow );

        void render();

    };





}