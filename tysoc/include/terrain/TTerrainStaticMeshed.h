

#pragma once

#include "TTerrain.h"
#include <LMesh.h>
#include <LMeshBuilder.h>

using namespace std;

namespace tysoc
{

    class TWorld;


    class TTerrainStaticMeshed : public TTerrain
    {
        private :

        engine::LMesh* m_mesh;
        btRigidBody* m_meshRigidBody;

        btBvhTriangleMeshShape* _initMeshBodyGeometry();
        btRigidBody* _initMeshRigidBody( btBvhTriangleMeshShape* pTriMeshShape );

        public :

        TTerrainStaticMeshed( TWorld* world );
        ~TTerrainStaticMeshed();

        static string getStaticType() { return string( "staticMeshed3d" ); }

        void update( float dt ) override;
        void setMaterial( const engine::LVec3& ambient,
                          const engine::LVec3& diffuse,
                          const engine::LVec3& specular,
                          float shininess ) override;

        engine::LMesh* getMesh() { return m_mesh; }
    };



}


