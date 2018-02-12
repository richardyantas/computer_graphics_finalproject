
#include <TPhysicsComponent.h>

using namespace std;



namespace tysoc
{



    TPhysicsComponent::TPhysicsComponent( TEntity* pParent )
        : TComponent( pParent )
    {

    }

    TPhysicsComponent::~TPhysicsComponent()
    {
        
    }

    void TPhysicsComponent::applyImpulse( const btVector3& impulse )
    {
        // Override this
    }

}