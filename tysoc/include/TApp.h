
#pragma once

#include <LWindow.h>
#include <LInputHandler.h>
#include <shaders/LShaderManager.h>
// #include <LAssetsManager.h>

#include "TWorld.h"
#include "TMasterRenderer.h"
#include "TDebugUI.h"

namespace tysoc
{


    class TApp
    {

        private :

        float m_tBef;
        float m_tNow;
        float m_tDelta;


        protected :

        TDebugUI * m_ui;
        TWorld* m_world;
        engine::LWindow* m_window;
        TMasterRenderer* m_masterRenderer;

        virtual void _customUpdate( float dt );

        public :

        static TApp* INSTANCE;

        TApp();
        ~TApp();

        virtual void init();
        virtual void dumpInfo();
        void run();

        TWorld* getWorld() { return m_world; }

        static void onKeyCallback( int key, int action );

    };



}