
#include <TApp.h>
#include <TPrimitiveEntity.h>

#include <LFixedCamera3d.h>
#include <LFpsCamera.h>
#include <LLightDirectional.h>

#include <cstdlib>

using namespace std;

#define SPHERE 0
#define BOX 1
#define CYLINDER 2
#define CAPSULE 3
#define MAX_PRIMITIVES 4

tysoc::TPrimitiveGraphicsParams s_gparams[MAX_PRIMITIVES];
tysoc::TPhysicsKinematicsParams s_pkParams[MAX_PRIMITIVES];
tysoc::TPhysicsDynamicsParams s_pdParams[MAX_PRIMITIVES];

class TestApp : public tysoc::TApp
{

    public :

    TestApp() : tysoc::TApp()
    {
        init();
    }

    void init() override;
};

void TestApp::init()
{
    cout << "initializing testapp" << endl;
    m_world = new tysoc::TWorld();

    //auto _camera = new engine::LFixedCamera3d( engine::LVec3( 22.8f, 17.8f, 22.1f ),
    //                                           engine::LVec3( -0.44f, -0.33f, -0.83f ),
    //                                           engine::LVec3( 0.0f, 1.0f, 0.0f ) );

    auto _camera = new engine::LFpsCamera( engine::LVec3( 10.0f, 0.0f, 10.0f ),
                                           engine::LVec3( 0.0f, 1.0f, 0.0f ) );

    auto _light = new engine::LLightDirectional( engine::LVec3( 0.1, 0.1, 0.1 ), engine::LVec3( 0.8, 0.8, 0.8 ),
                                                 engine::LVec3( 0.05, 0.05, 0.05 ), 0, engine::LVec3( -1, -1, -1 ) );

    _light->setVirtualPosition( engine::LVec3( 5, 5, 0 ) );
    
    m_world->addCamera( _camera, "mainCamera" );
    m_world->addLight( _light );

    // construction params
    // TODO: Change to a single constructiont struct - geometry construction info
    
    tysoc::TPrimitiveGraphicsParams _gSphere;
    _gSphere.sphere_radius = 1.0f;
    s_gparams[SPHERE] = _gSphere;

    tysoc::TPrimitiveGraphicsParams _gBox;
    _gBox.box_width = 1.5f;
    _gBox.box_height = 0.5f;
    _gBox.box_depth = 1.0f;
    s_gparams[BOX] = _gBox;

    tysoc::TPrimitiveGraphicsParams _gCylinder;
    _gCylinder.cylinder_baseRadius = 0.5f;
    _gCylinder.cylinder_length = 2.0f;
    s_gparams[CYLINDER] = _gCylinder;

    tysoc::TPrimitiveGraphicsParams _gCapsule;
    _gCapsule.capsule_baseRadius = 0.5f;
    _gCapsule.capsule_length = 2.0f;
    s_gparams[CAPSULE] = _gCapsule;

    // kinematics info

    tysoc::TPhysicsKinematicsParams _kSphere;
    _kSphere.sphere_radius = _gSphere.sphere_radius;
    s_pkParams[SPHERE] = _kSphere;
    
    tysoc::TPhysicsKinematicsParams _kBox;
    _kBox.box_width = _gBox.box_width;
    _kBox.box_height = _gBox.box_height;
    _kBox.box_depth = _gBox.box_depth;
    s_pkParams[BOX] = _kBox;

    tysoc::TPhysicsKinematicsParams _kCylinder;
    _kCylinder.cylinder_baseRadius = _gCylinder.cylinder_baseRadius;
    _kCylinder.cylinder_length = _gCylinder.cylinder_length;
    s_pkParams[CYLINDER] = _kCylinder;

    tysoc::TPhysicsKinematicsParams _kCapsule;
    _kCapsule.capsule_baseRadius = _gCapsule.capsule_baseRadius;
    _kCapsule.capsule_length = _gCapsule.capsule_length;
    s_pkParams[CAPSULE] = _kCapsule;

    // dynamics info
    tysoc::TPhysicsDynamicsParams _dParams;
    _dParams.mass = 0.0f;
    _dParams.restitution = 0.5f;

    s_pdParams[SPHERE] = _dParams;
    s_pdParams[BOX] = _dParams;
    s_pdParams[CYLINDER] = _dParams;
    s_pdParams[CAPSULE] = _dParams;

    {
        int _primitiveId = BOX;

        auto _entity = new tysoc::TPrimitiveEntity( tysoc::TVec3(0,2,0), tysoc::TVec3(),
                                                       (tysoc::_primitiveGraphicsType)_primitiveId, ( tysoc::_primitiveCollisionType ) _primitiveId,
                                                       s_gparams[_primitiveId], s_pkParams[_primitiveId], s_pdParams[_primitiveId] );

        auto _renderable = _entity->getComponent< tysoc::TGraphicsComponent >()->getRenderable();
        auto _material = _renderable->getMaterial();
        _material->ambient = tysoc::TVec3( 1, 0, 0 );
        _material->diffuse = tysoc::TVec3( 1, 0, 0 );
        _material->specular = tysoc::TVec3( 1, 0, 0 );

        m_world->addEntity( _entity );
    }

    {
        int _primitiveId = CYLINDER;

        auto _entity = new tysoc::TPrimitiveEntity( tysoc::TVec3(2,2,0), tysoc::TVec3(),
                                                       (tysoc::_primitiveGraphicsType)_primitiveId, ( tysoc::_primitiveCollisionType ) _primitiveId,
                                                       s_gparams[_primitiveId], s_pkParams[_primitiveId], s_pdParams[_primitiveId] );

        auto _renderable = _entity->getComponent< tysoc::TGraphicsComponent >()->getRenderable();
        auto _material = _renderable->getMaterial();
        _material->ambient = tysoc::TVec3( 0, 1, 0 );
        _material->diffuse = tysoc::TVec3( 0, 1, 0 );
        _material->specular = tysoc::TVec3( 0, 1, 0 );

        m_world->addEntity( _entity );
    }

    {
        int _primitiveId = SPHERE;

        auto _entity = new tysoc::TPrimitiveEntity( tysoc::TVec3(4,2,0), tysoc::TVec3(),
                                                       (tysoc::_primitiveGraphicsType)_primitiveId, ( tysoc::_primitiveCollisionType ) _primitiveId,
                                                       s_gparams[_primitiveId], s_pkParams[_primitiveId], s_pdParams[_primitiveId] );

        auto _renderable = _entity->getComponent< tysoc::TGraphicsComponent >()->getRenderable();
        auto _material = _renderable->getMaterial();
        _material->ambient = tysoc::TVec3( 0, 1, 1 );
        _material->diffuse = tysoc::TVec3( 0, 1, 1 );
        _material->specular = tysoc::TVec3( 0, 1, 1 );

        m_world->addEntity( _entity );
    }

    {
        int _primitiveId = CAPSULE;

        auto _entity = new tysoc::TPrimitiveEntity( tysoc::TVec3(6,2,0), tysoc::TVec3(),
                                                       (tysoc::_primitiveGraphicsType)_primitiveId, ( tysoc::_primitiveCollisionType ) _primitiveId,
                                                       s_gparams[_primitiveId], s_pkParams[_primitiveId], s_pdParams[_primitiveId] );

        auto _renderable = _entity->getComponent< tysoc::TGraphicsComponent >()->getRenderable();
        auto _material = _renderable->getMaterial();
        _material->ambient = tysoc::TVec3( 1, 1, 0 );
        _material->diffuse = tysoc::TVec3( 1, 1, 0 );
        _material->specular = tysoc::TVec3( 1, 1, 0 );

        m_world->addEntity( _entity );
    }

    cout << "done initializing testapp" << endl;
}

int main()
{
    auto _app = new TestApp();

    _app->run();

    delete _app;

    return 0;
}