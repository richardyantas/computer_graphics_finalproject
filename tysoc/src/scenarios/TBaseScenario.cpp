
#include <scenarios/TBaseScenario.h>


namespace tysoc
{

    TBaseScenario::TBaseScenario()
        : TWorld()
    {
        m_mainLight = new engine::LLightDirectional( engine::LVec3( 0.2, 0.2, 0.2 ), engine::LVec3( 0.8, 0.8, 0.8 ),
                                                     engine::LVec3( 0.05, 0.05, 0.05 ), 0, engine::LVec3( -1, -1, 0 ) );

        m_mainLight->setVirtualPosition( engine::LVec3( 5, 5, 0 ) );

        //m_mainCamera = new engine::LFixedCamera3d( engine::LVec3( -4.5f, 4.7f, -5.9f ),
        //                                           engine::LVec3( 0.65f, -0.38f, 0.65f ),
        //                                           engine::LVec3( 0.0f, 1.0f, 0.0f ) );

        m_mainCamera = new engine::LFixedCamera3d( engine::LVec3( 2.71f, 4.28f, 3.68f ),
                                                   engine::LVec3( -0.20f, -0.45f, -0.87f ),
                                                   engine::LVec3( 0.0f, 1.0f, 0.0f ) );

        m_freeCamera = new engine::LFpsCamera( engine::LVec3( 1.0f, 2.0f, -1.0f ),
                                               engine::LVec3( 0.0f, 1.0f, 0.0f ) );

        m_sideCamera = new engine::LFixedCamera3d( engine::LVec3( 1.0f, 3.0f, 5.0f ),
                                                   engine::LVec3( 0.0f, 0.0f, -1.0f ),
                                                   engine::LVec3( 0.0f, 1.0f, 0.0f ) );

        m_player = new TPlayerEntity( TVec3( 1, 3, 0 ) );

        m_camMainDeltaFromPlayer = m_mainCamera->getPosition() - m_player->pos;
        m_camSideDeltaFromPlayer = m_sideCamera->getPosition() - m_player->pos;

        addCamera( m_mainCamera, "mainCamera" );
        addCamera( m_sideCamera, "sideCamera" );
        addCamera( m_freeCamera, "freeCamera" );
        addLight( m_mainLight );
        addEntity( m_player );

        initTerrain();
    }

    TBaseScenario::~TBaseScenario()
    {
        m_mainCamera = NULL;
        m_sideCamera = NULL;
        m_freeCamera = NULL;
        m_player = NULL;
        m_mainLight = NULL;
    }

    void TBaseScenario::initTerrain()
    {
        setTerrain( new TTerrain1DPatched( this ) );
    }

    void TBaseScenario::update( float dt )
    {
        TWorld::update( dt );

        // Make the main camera follow the player
        m_mainCamera->setPosition( m_player->pos + m_camMainDeltaFromPlayer );

        // Make the side camera follow the player
        m_sideCamera->setPosition( m_player->pos + m_camSideDeltaFromPlayer );
    }


}