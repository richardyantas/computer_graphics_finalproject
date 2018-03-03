
#pragma once

#include <TWorld.h>
#include <LLightDirectional.h>
#include <LFixedCamera3d.h>
#include <LFpsCamera.h>
#include <TPlayerEntity.h>
#include <TTerrain1DPatched.h>
#include <TPrimitiveEntity.h>
#include <sim/TSimCharacterEntity.h>

#define OBSTACLE_SPHERE 0
#define OBSTACLE_BOX 1
#define OBSTACLE_CYLINDER 2
#define OBSTACLE_CAPSULE 3
#define OBSTACLE_MAX_PRIMITIVES 4

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
        TSimCharacterEntity* m_simCharacter;

        engine::LVec3 m_mainLightDeltaFromPlayer;
        engine::LVec3 m_camMainDeltaFromPlayer;
        engine::LVec3 m_camSideDeltaFromPlayer;

        TPrimitiveGraphicsParams m_gparams[4];
        TPhysicsKinematicsParams m_pkParams[4];
        TPhysicsDynamicsParams m_pdParams[4];

        public :

        TBaseScenario();
        ~TBaseScenario();

        virtual void initTerrain();

        void update( float dt ) override;

        void createObstacle();

        TPlayerEntity* getPlayer() { return m_player; }
    };





}