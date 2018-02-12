
#include <TGraphicsComponent.h>

using namespace std;


namespace tysoc
{

    TGraphicsComponent::TGraphicsComponent( TEntity* parent )
        : TComponent( parent )
    {
        this->type = TGraphicsComponent::getStaticType();
        
        m_renderable = NULL;
    }

    TGraphicsComponent::~TGraphicsComponent()
    {

        if ( m_renderable != NULL )
        {
            delete m_renderable;
            m_renderable = NULL;
        }
    }

    void TGraphicsComponent::update( float dt )
    {
        // cout << "update gcomponent" << endl;

        m_renderable->pos = m_parent->pos;
        m_renderable->rotation = m_parent->rotation;
    }

}