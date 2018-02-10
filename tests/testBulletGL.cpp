
#include <LWindow.h>
#include <LInputHandler.h>
#include <LShaderManager.h>
#include <LFpsCamera.h>
#include <LFixedCamera3d.h>
#include <LMeshBuilder.h>
#include <LShaderBasic3d.h>

#include <iostream>
#define BT_USE_DOUBLE_PRECISION
#include <btBulletDynamicsCommon.h>

using namespace std;


int main()
{
    auto _window = new engine::LWindow();

    engine::LInputHandler::create( _window );
    engine::LShaderManager::create();

    // auto _camera = new engine::LFpsCamera( engine::LVec3( -1.0f, 1.0f, 0.0f ),
    //                                        engine::LVec3( 0.0f, 1.0f, 0.0f ) );
    auto _camera = new engine::LFixedCamera3d( engine::LVec3( 0.0f, 0.0f, 20.0f ),
                                               engine::LVec3( 0.0f, 0.0f, -20.0f ),
                                               engine::LVec3( 0.0f, 1.0f, 0.0f ) );

    auto _sphere = engine::LMeshBuilder::createSphere( 1.0f, 15, 15 );
    _sphere->drawAsWireframe = true;

    // bullet stuff

    btBroadphaseInterface* broadphase = new btDbvtBroadphase();

    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -10, 0));

    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
    btCollisionShape* fallShape = new btSphereShape(1);

    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
    btRigidBody::btRigidBodyConstructionInfo
                groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    groundRigidBody->setRestitution( 1.f );
    dynamicsWorld->addRigidBody(groundRigidBody);

    btDefaultMotionState* fallMotionState =
                new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 7.5, 0)));
    btScalar mass = 1;
    btVector3 fallInertia(0, 0, 0);
    fallShape->calculateLocalInertia(mass, fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
    btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
    dynamicsWorld->addRigidBody(fallRigidBody);
    fallRigidBody->setRestitution( 1.0f );

    // end bullet stuff creation

    while ( _window->isActive() )
    {
        _window->clear();
        _window->pollEvents();

        _camera->update( 0.02 );

        dynamicsWorld->stepSimulation( 1 / 60.f, 10 );
        btTransform trans;
        fallRigidBody->getMotionState()->getWorldTransform(trans);

        std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;

        _sphere->pos.y = trans.getOrigin().getY();

        auto _shader = ( engine::LShaderBasic3d* ) engine::LShaderManager::INSTANCE->programObjs["basic3d"];

        _shader->bind();

        _shader->setViewMatrix( _camera->getViewMatrix() );
        _shader->setProjectionMatrix( _camera->getProjectionMatrix() );

        {
            _shader->setModelMatrix( _sphere->getModelMatrix() );
            _shader->setPlainColor( engine::LVec3( 0, 0, 255 ) );
            _sphere->render();
        }


        _shader->unbind();

        _window->swapBuffers();
    }


    delete _camera;
    delete _window;
    delete _sphere;

    dynamicsWorld->removeRigidBody(fallRigidBody);
    delete fallRigidBody->getMotionState();
    delete fallRigidBody;

    dynamicsWorld->removeRigidBody(groundRigidBody);
    delete groundRigidBody->getMotionState();
    delete groundRigidBody;

    delete fallShape;
    delete groundShape;

    delete dynamicsWorld;
    delete solver;
    delete collisionConfiguration;
    delete dispatcher;
    delete broadphase;

    return 0;
}



