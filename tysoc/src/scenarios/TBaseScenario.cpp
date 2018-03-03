
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

        m_simCharacter = new TSimCharacterEntity( "raptor.txt", TVec3( 0, 3, 0 ) );

        m_camMainDeltaFromPlayer = m_mainCamera->getPosition() - m_player->pos;
        m_camSideDeltaFromPlayer = m_sideCamera->getPosition() - m_player->pos;
        m_mainLightDeltaFromPlayer = m_mainLight->getVirtualPosition() - m_player->pos;

        addCamera( m_mainCamera, "mainCamera" );
        addCamera( m_sideCamera, "sideCamera" );
        addCamera( m_freeCamera, "freeCamera" );
        addLight( m_mainLight );
        addEntity( m_player );


        TPrimitiveGraphicsParams _gSphere;
        _gSphere.sphere_radius = 0.25f;
        m_gparams[OBSTACLE_SPHERE] = _gSphere;

        TPrimitiveGraphicsParams _gBox;
        _gBox.box_width = 0.25f;
        _gBox.box_height = 0.25f;
        _gBox.box_depth = 0.25f;
        m_gparams[OBSTACLE_BOX] = _gBox;

        TPrimitiveGraphicsParams _gCylinder;
        _gCylinder.cylinder_baseRadius = 0.1f;
        _gCylinder.cylinder_length = 0.2f;
        m_gparams[OBSTACLE_CYLINDER] = _gCylinder;

        tysoc::TPrimitiveGraphicsParams _gCapsule;
        _gCapsule.capsule_baseRadius = 0.1f;
        _gCapsule.capsule_length = 0.2f;
        m_gparams[OBSTACLE_CAPSULE] = _gCapsule;

        // kinematics info

        TPhysicsKinematicsParams _kSphere;
        _kSphere.sphere_radius = _gSphere.sphere_radius;
        m_pkParams[OBSTACLE_SPHERE] = _kSphere;
        
        TPhysicsKinematicsParams _kBox;
        _kBox.box_width = _gBox.box_width;
        _kBox.box_height = _gBox.box_height;
        _kBox.box_depth = _gBox.box_depth;
        m_pkParams[OBSTACLE_BOX] = _kBox;

        TPhysicsKinematicsParams _kCylinder;
        _kCylinder.cylinder_baseRadius = _gCylinder.cylinder_baseRadius;
        _kCylinder.cylinder_length = _gCylinder.cylinder_length;
        m_pkParams[OBSTACLE_CYLINDER] = _kCylinder;

        TPhysicsKinematicsParams _kCapsule;
        _kCapsule.capsule_baseRadius = _gCapsule.capsule_baseRadius;
        _kCapsule.capsule_length = _gCapsule.capsule_length;
        m_pkParams[OBSTACLE_CAPSULE] = _kCapsule;

        // dynamics info
        TPhysicsDynamicsParams _dParams;
        _dParams.mass = 1.0f;
        _dParams.restitution = 0.5f;

        m_pdParams[OBSTACLE_SPHERE] = _dParams;
        m_pdParams[OBSTACLE_BOX] = _dParams;
        m_pdParams[OBSTACLE_CYLINDER] = _dParams;
        m_pdParams[OBSTACLE_CAPSULE] = _dParams;


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

        // Make the light follow the player
        m_mainLight->setVirtualPosition( m_player->pos + m_mainLightDeltaFromPlayer );
    }

    void TBaseScenario::createObstacle()
    {
        int _primitiveId = rand() % OBSTACLE_MAX_PRIMITIVES;

        auto _pos = m_player->pos;
        _pos.x += 0.0f;
        _pos.y += 2.0f;
        _pos.z += 0.0f;

        auto _entity = new tysoc::TPrimitiveEntity( _pos, tysoc::TVec3(),
                                                    (tysoc::_primitiveGraphicsType)_primitiveId, ( tysoc::_primitiveCollisionType ) _primitiveId,
                                                    m_gparams[_primitiveId], m_pkParams[_primitiveId], m_pdParams[_primitiveId] );

        addEntity( _entity );
    }
}