
#include <sim/TSimCharacterEntity.h>

using namespace std;


namespace tysoc
{


    TSimCharacterEntity::TSimCharacterEntity( const string& structureFile,
                                              const TVec3& initialPosition )
    {
        m_characterTree = new TCharacterNode();

        TCharacterParser::parseCharacter( *m_characterTree, structureFile );

        // addComponent( new TSimCharacterGraphicsComponent( this, m_characterTree ) );
        // addComponent( new TSimCharacterPhysicsComponent( this, m_characterTree ) );
    }

    TSimCharacterEntity::~TSimCharacterEntity()
    {
        delete m_characterTree;
        m_characterTree = NULL;
    }

    void TSimCharacterEntity::setBodyComponentTransform( string id, const glm::mat4& transform )
    {
        m_bodiesTransforms[ id ] = transform;
    }

    glm::mat4 TSimCharacterEntity::getBodyComponentTransform( string id )
    {
        if ( m_bodiesTransforms.find( id ) == m_bodiesTransforms.end() )
        {
            cout << "transform for body with id: " << id << " not found" << endl;
            return glm::mat4( 1.0f );
        }

        return m_bodiesTransforms[ id ];
    }

}