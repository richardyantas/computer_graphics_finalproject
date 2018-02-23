
#pragma once

#include <LUIHandler.h>
#include <TWorld.h>

using namespace cat1UI;

namespace tysoc
{


    class TDebugUI
    {

        private :

        LUIHandler* m_uiHandler;
        TWorld* m_world;

        LUIWindow* m_windowMaster;
        LUIWindow* m_windowLighting;
        LUIWindow* m_windowTestPanel;

        public :

        TDebugUI( GLFWwindow* pGlfwWindow );
        ~TDebugUI();

        void init( TWorld* pWorld );

        void render();


    };




}