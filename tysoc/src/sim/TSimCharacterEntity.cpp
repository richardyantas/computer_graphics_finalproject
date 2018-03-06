
#include <sim/TSimCharacterEntity.h>

using namespace std;


namespace tysoc
{


    TSimCharacterEntity::TSimCharacterEntity( const string& structureFile,
                                              const TVec3& initialPosition )
		: TEntity( initialPosition )
    {
        m_characterTree = new TCharacterNode();

        TCharacterParser::parseCharacter( *m_characterTree, structureFile );

		auto _graphicsComponent = new TSimCharacterGraphicsComponent( this, m_characterTree );
        m_numDof = _graphicsComponent->getNumDof();
        m_pose = vector< float >( m_numDof, 0.0f );

        //auto _motionComponent = new TSimCharacterMotionComponent( this, "raptor_run.json" );

		auto _physicsComponent = new TSimCharacterPhysicsComponent( this, m_characterTree );

		addComponent( _physicsComponent );
		//addComponent( _motionComponent );
		addComponent( _graphicsComponent );
        
		
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

    void TSimCharacterEntity::setPose( const vector< float >& pose )
    {
        if ( pose.size() != m_numDof )
        {
            cout << "dof mismatch - ext. pose : " << pose.size() << " - this : " << m_numDof << endl;
            return;
        }

        for ( int q = 0; q < m_numDof; q++ )
        {
            m_pose[q] = pose[q];
        }
    }

    void TSimCharacterEntity::getPose( vector< float >& pose )
    {
        if ( pose.size() != m_numDof )
        {
            cout << "dof mismatch - ext. pose : " << pose.size() << " - this : " << m_numDof << endl;
            return;
        }
        
        for ( int q = 0; q < m_numDof; q++ )
        {
            pose[q] = m_pose[q];
        }
    }

}