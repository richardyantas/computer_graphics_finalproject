
#pragma once

#include <TWorld.h>
#include <LLightDirectional.h>
#include <LFixedCamera3d.h>
#include <LFpsCamera.h>
#include <TPlayerEntity.h>
#include <TTerrain1DPatched.h>

using namespace std;

namespace tysoc
{

    class TBaseScenario : public TWorld
    {

        protected :

        engine::LLightDirectional* m_mainLight;

        engine::LFixedCamera3d* m_mainCamera;
        engine::LFixedCamera3d* m_sideCamera;
        engine::LFpsCamera* m_freeCamera;

        TPlayerEntity* m_player;

        engine::LVec3 m_camMainDeltaFromPlayer;
        engine::LVec3 m_camSideDeltaFromPlayer;

        public :

        TBaseScenario();
        ~TBaseScenario();

        virtual void initTerrain();

        void update( float dt ) override;


        TPlayerEntity* getPlayer() { return m_player; }
    };





}