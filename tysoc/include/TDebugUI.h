
#pragma once

#include <TCommon.h>
#include <LUIHandler.h>
#include <scenarios/TBaseScenario.h>
#include <TPlayerEntity.h>
#include <debug/LDebugSystem.h>

using namespace cat1UI;
using namespace std;

namespace tysoc
{


    class TDebugUI
    {

        private :

        LUIHandler* m_uiHandler;
        TBaseScenario* m_scenario;

        LUIWindow* m_wMaster;
        LUIWindow* m_wCamInfo;
        LUIWindow* m_wPlayerInfo;
        LUIWindow* m_wLighting;
        LUIWindow* m_wTestPanel;

        TPlayerEntity* m_playerRef;

        string _makeText( string title, string msg );

        public :

        TDebugUI( GLFWwindow* pGlfwWindow );
        ~TDebugUI();

        void init( TBaseScenario* pScenario );

        void render();


    };




}