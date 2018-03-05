
#include <TWorld.h>

#include <TGraphicsComponent.h>
#include <TPhysicsComponent.h>
#include <TBasicPhysicsComponent.h>
#include <TBasicGraphicsComponent.h>
#include <TPrimitivePhysicsComponent.h>
#include <sim/TSimCharacterPhysicsComponent.h>
#include <TPrimitiveGraphicsComponent.h>


using namespace std;



namespace tysoc
{

    TWorld::TWorld()
    {
        m_currentCamera = NULL;
        m_terrain = NULL;

        m_globalAmbientLight = WORLD_DEFAULT_AMBIENT_LIGHT;

        m_btBroadphase = new btDbvtBroadphase();
        m_btCollisionConfiguration = new btDefaultCollisionConfiguration();
        m_btCollisionDispatcher = new btCollisionDispatcher( m_btCollisionConfiguration );
        m_btSolver = new btSequentialImpulseConstraintSolver();
        m_btWorld = new btDiscreteDynamicsWorld( m_btCollisionDispatcher, 
                                                 m_btBroadphase, 
                                                 m_btSolver, 
                                                 m_btCollisionConfiguration );

        m_btWorld->setGravity( btVector3( 0, -10, 0 ) );

        {
            // TODO: Fix this ugly leaky initialization

            auto _planeShape = new btStaticPlaneShape( btVector3( 0, 1, 0 ), 0 );
            auto _planeMotionState = new btDefaultMotionState( btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, 0, 0 ) ) );
            btRigidBody::btRigidBodyConstructionInfo _planeRigidBodyCI( 0, _planeMotionState, _planeShape, btVector3( 0, 0, 0 ) );

            auto _planeBody = new btRigidBody( _planeRigidBodyCI );
            _planeBody->setRestitution( 0.95 );
            _planeBody->setFriction( 1.0 );

            auto _planeMesh = engine::LMeshBuilder::createPlane( 30, 30 );

            _planeMesh->getMaterial()->ambient  = engine::LVec3( 0, 0, 1 );
            _planeMesh->getMaterial()->diffuse  = engine::LVec3( 0, 0, 1 );
            _planeMesh->getMaterial()->specular = engine::LVec3( 0, 0, 1 );

            auto _planeEntity = new TEntity();
            auto _planeGComponent = new TBasicGraphicsComponent( _planeEntity, _planeMesh );
            auto _planePComponent = new TBasicPhysicsComponent( _planeEntity, _planeBody );
            _planeEntity->addComponent( _planeGComponent );
            _planeEntity->addComponent( _planePComponent );

            //addEntity( _planeEntity );
            m_btWorld->addRigidBody( _planeBody );
        }
    }

    TWorld::~TWorld()
    {
        for ( auto _it = m_cameras.begin(); _it != m_cameras.end(); ++_it )
        {
            delete _it->second;
        }
        m_cameras.clear();

        for ( auto _light : m_lights )
        {
            delete _light;
        }
        m_lights.clear();
    }

    void TWorld::addCamera( engine::LICamera* pCamera, string cameraStrId )
    {
        if ( m_cameras.find( cameraStrId ) == m_cameras.end() )
        {
            m_cameras[ cameraStrId ] = pCamera;
            if ( m_currentCamera == NULL )
            {
                m_currentCamera = pCamera;
            }
        }
        else
        {
            cout << "TWorld::addCamera> camera with id: " << cameraStrId << " already in map" << endl;
        }
    }

    void TWorld::changeToCamera( string cameraStrId )
    {
        if ( m_cameras.find( cameraStrId ) == m_cameras.end() )
        {
            cout << "TWorld::changeToCamera> can't change to camera with id: " << cameraStrId << ", it doesn't exist" << endl;
        }
        else
        {
            m_currentCamera = m_cameras[ cameraStrId ];
        }
    }

    void TWorld::update( float dt )
    {
        if ( m_currentCamera != NULL )
        {
            m_currentCamera->update( dt );
        }

        for ( auto _entity : m_entities )
        {
            _entity->update( dt );
        }

        if ( m_terrain != NULL )
        {
            m_terrain->update( dt );
        }

        m_btWorld->stepSimulation( 1 / 60.f, 1 );
    }
 
    void TWorld::addEntity( TEntity* pEntity )
    {
        m_entities.push_back( pEntity );

        // TODO: Modify this part by making the components self additive

        auto _physicsComponent = pEntity->getComponent< TPhysicsComponent >();
        if ( _physicsComponent != NULL )
        {
            if ( _physicsComponent->type == TBasicPhysicsComponent::getStaticType() )
            {
                auto _basicPhysicsComponent = reinterpret_cast< TBasicPhysicsComponent* >( _physicsComponent );

                m_btWorld->addRigidBody( _basicPhysicsComponent->getRigidBody() );
            }
        }

        _physicsComponent = pEntity->getComponent< TBasicPhysicsComponent >();
        if ( _physicsComponent != NULL )
        {
            if ( _physicsComponent->type == TBasicPhysicsComponent::getStaticType() )
            {
                auto _basicPhysicsComponent = reinterpret_cast< TBasicPhysicsComponent* >( _physicsComponent );

                m_btWorld->addRigidBody( _basicPhysicsComponent->getRigidBody() );
            }            
        }

        _physicsComponent = pEntity->getComponent< TPrimitivePhysicsComponent >();
        if ( _physicsComponent != NULL )
        {
            if ( _physicsComponent->type == TPrimitivePhysicsComponent::getStaticType() )
            {
                auto _primitivePhysicsComponent = reinterpret_cast< TPrimitivePhysicsComponent* >( _physicsComponent );

                m_btWorld->addRigidBody( _primitivePhysicsComponent->getRigidBody() );
            }            
        }

        //_physicsComponent = pEntity->getComponent< TSimCharacterPhysicsComponent >();
        //if ( _physicsComponent != NULL )
        //{
        //    
        //}
    }

    void TWorld::dumpInfo()
    {
        if ( m_currentCamera != NULL )
        {
            m_currentCamera->dumpInfo();
        }
    }
}