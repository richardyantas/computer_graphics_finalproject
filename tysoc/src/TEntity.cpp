

#include <TEntity.h>

using namespace std;

namespace tysoc
{

    TEntity::TEntity()
    {
        rotation = glm::mat4( 1.0f );
    }

    TEntity::TEntity( const engine::LVec3& initialPosition )
    {
        rotation = glm::mat4( 1.0f );
        pos = initialPosition;
    }

    TEntity::~TEntity()
    {
        for ( auto _it = m_components.begin(); _it != m_components.end(); ++_it )
        {
            delete _it->second;
        }
        
        m_components.clear();
    }

    void TEntity::addComponent( TComponent* pComponent )
    {
        m_components[ pComponent->type ] = pComponent;
    }

    void TEntity::update( float dt )
    {
        for ( auto _it = m_components.begin(); _it != m_components.end(); ++_it )
        {
            _it->second->update( dt );
        }
    }
}