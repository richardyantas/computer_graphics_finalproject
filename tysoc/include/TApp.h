
#pragma once

#include <LWindow.h>
#include <LInputHandler.h>
#include <LShaderManager.h>
// #include <LAssetsManager.h>

#include "TWorld.h"
#include "TMasterRenderer.h"

namespace tysoc
{


    class TApp
    {

        private :

        float m_tBef;
        float m_tNow;
        float m_tDelta;

        protected :

        TWorld* m_world;
        engine::LWindow* m_window;
        TMasterRenderer* m_masterRenderer;

        public :

        TApp();
        ~TApp();

        virtual void init();

        void run();
    };



}