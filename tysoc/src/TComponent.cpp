
#include <TComponent.h>

using namespace std;


namespace tysoc
{


    TComponent::TComponent( TEntity* pParent )
    {
        m_parent = pParent;
        type = TComponent::getStaticType();
    }

    TComponent::~TComponent()
    {
        m_parent = NULL;
    }


    string TComponent::getStaticType()
    {
        return string( "base" );
    }

    void TComponent::update( float dt )
    {
        // Override this
    }

}