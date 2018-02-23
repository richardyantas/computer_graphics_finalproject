
#include <TBasicGraphicsComponent.h>

using namespace std;



namespace tysoc
{


    TBasicGraphicsComponent::TBasicGraphicsComponent( TEntity* pParent )
        : TGraphicsComponent( pParent )
    {
        auto _mesh = engine::LMeshBuilder::createSphere( 0.2, 15, 15 );
        setRenderable( _mesh );
    }

    TBasicGraphicsComponent::TBasicGraphicsComponent( TEntity* pParent, engine::LMesh* pMesh )
        : TGraphicsComponent( pParent )
    {
        setRenderable( pMesh );
    }

    TBasicGraphicsComponent::~TBasicGraphicsComponent()
    {

    }

}
