
#include <terrain/TTerrainStaticMeshed.h>

using namespace std;


namespace tysoc
{



    TTerrainStaticMeshed::TTerrainStaticMeshed( TWorld* pWorld )
        : TTerrain( pWorld )
    {
        m_type = TTerrainStaticMeshed::getStaticType();

        m_mesh = engine::LMeshBuilder::createPerlinPatch( 100, 100, 100 );
        setMaterial( TERRAIN1D_MATERIAL_AMBIENT_COMPONENT,
                     TERRAIN1D_MATERIAL_DIFFUSE_COMPONENT,
                     TERRAIN1D_MATERIAL_SPECULAR_COMPONENT,
                     TERRAIN1D_MATERIAL_SHININESS_COMPONENT );
        // m_mesh->pos.y -= 2.0f;

        btBvhTriangleMeshShape* _meshShape = _initMeshBodyGeometry();
        m_meshRigidBody = _initMeshRigidBody( _meshShape );

        m_world->getBulletWorld()->addRigidBody( m_meshRigidBody );
    }

    btBvhTriangleMeshShape* TTerrainStaticMeshed::_initMeshBodyGeometry()
    {
        btTriangleIndexVertexArray* _meshInterface = new btTriangleIndexVertexArray();
        btIndexedMesh _meshPart;

        auto& _vertices = m_mesh->vertices();
        auto& _indices  = m_mesh->indices();

        cout << "vsize: " << _vertices.size() << endl;
        cout << "isize: " << _indices.size() << endl;

        _meshPart.m_vertexBase = ( const unsigned char* ) _vertices.data();
        _meshPart.m_vertexStride = sizeof( engine::LVec3 );
        _meshPart.m_numVertices = _vertices.size();
        _meshPart.m_triangleIndexBase = ( const unsigned char* ) _indices.data();
        _meshPart.m_triangleIndexStride = sizeof( engine::LInd3 );
        _meshPart.m_numTriangles = _indices.size();
        _meshPart.m_indexType = PHY_INTEGER;
        _meshPart.m_vertexType = PHY_FLOAT;

        _meshInterface->addIndexedMesh( _meshPart, PHY_INTEGER );

        bool _useQuantizedAabbCompression = true;
        btBvhTriangleMeshShape* _triMeshShape = new btBvhTriangleMeshShape( _meshInterface, 
                                                                            _useQuantizedAabbCompression );
        return _triMeshShape;
    }

    btRigidBody* TTerrainStaticMeshed::_initMeshRigidBody( btBvhTriangleMeshShape* pTriMeshShape )
    {
        btVector3 _localInertia( 0, 0, 0 );
        btTransform _transform;
        _transform.setIdentity();
        // _transform.setOrigin( btVector3( 0, -2, 0 ) );

        btDefaultMotionState* _motionState = new btDefaultMotionState( _transform );
        
        btRigidBody::btRigidBodyConstructionInfo _rbInfo( 0, _motionState, pTriMeshShape, _localInertia);
        auto _rigidBody = new btRigidBody( _rbInfo );

        _rigidBody->setFriction( btScalar( 0.9 ) );
        _rigidBody->setRestitution( 0.9f );

        return _rigidBody;
    }


    void TTerrainStaticMeshed::update( float dt )
    {

    }

    void TTerrainStaticMeshed::setMaterial( const engine::LVec3& ambient,
                                            const engine::LVec3& diffuse,
                                            const engine::LVec3& specular,
                                            float shininess )
    {
        auto _material = m_mesh->getMaterial();
        _material->ambient = ambient;
        _material->diffuse = diffuse;
        _material->specular = specular;
        _material->shininess = shininess;
    }
}