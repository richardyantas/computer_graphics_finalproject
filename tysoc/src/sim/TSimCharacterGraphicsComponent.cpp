
#include <sim/TSimCharacterGraphicsComponent.h>



using namespace std;

namespace tysoc
{


    TSimCharacterGraphicsComponent::TSimCharacterGraphicsComponent( TSimCharacterEntity* pParent, TCharacterNode* tree,
    																bool useFramesMotion )
        : TGraphicsComponent( pParent )
    {
		m_numDof = 0;

		m_usesMotion = useFramesMotion;

        m_characterTree = tree;
		m_characterRef = pParent;
		this->type = TSimCharacterGraphicsComponent::getStaticType();
        _buildFromTree();

        m_pose = vector< float >( m_numDof, 0.0f );
    }

    TSimCharacterGraphicsComponent::~TSimCharacterGraphicsComponent()
    {
        m_characterTree = NULL;
		m_characterRef = NULL;
    }

    void TSimCharacterGraphicsComponent::_buildFromTree()
    {
        _buildNode( m_characterTree, glm::mat4( 1.0f ) );
    }

    void TSimCharacterGraphicsComponent::_buildNode( TCharacterNode* node, glm::mat4 cumTransform )
    {
        m_numDof++;

        auto& _nodeData = node->data;
        auto& _drawData = _nodeData.drawData;
		auto& _jointData = _nodeData.jointData;
		auto& _pdcData = _nodeData.pdcData;

        engine::LMesh* _mesh = NULL;

        switch ( g_GraphicsShapeMap[ _drawData.shape ] )
        {
            case GRAPHICS_BOX :

                _mesh = engine::LMeshBuilder::createBox( _drawData.param0,
                                                         _drawData.param1,
                                                         _drawData.param2 );

            break;

            default :
                cout << "gtype: " << _drawData.shape << " is not supported" << endl;
            break;
        }

		if ( _mesh != NULL )
		{
			_mesh->getMaterial()->ambient  = _drawData.color;
			_mesh->getMaterial()->diffuse  = _drawData.color;
			_mesh->getMaterial()->specular = _drawData.color;

			cumTransform = _jointData.localTransform * cumTransform;

            glm::mat4 _worldTransform = _drawData.localTransform * cumTransform;

			glm::vec3 _pos = _worldTransform[3];
			glm::mat3 _rot = glm::mat3( _worldTransform );
			_mesh->pos = TVec3( _pos.x, _pos.y, _pos.z );
			_mesh->rotation = glm::mat4( _rot );

			m_bodyMeshes[node->name] = _mesh;
			m_jointAngles[node->name] = _pdcData.targetAngle;
		}


		for ( int q = 0; q < node->children.size(); q++ )
		{
			_buildNode( node->children[q], cumTransform );
		}
    }

	void TSimCharacterGraphicsComponent::_setNodeTransform( TCharacterNode* node,
														   glm::mat4 cumWorldTransform )
	{
		auto _nodeMesh = m_bodyMeshes[node->name];

        int _nodeIndx = node->id;
        float _poseAngle = m_pose[ _nodeIndx ];

        // update by the current joint transformation
		glm::mat4 _jointTransform = glm::translate( node->data.jointData.pivot ) *
									glm::rotate( _poseAngle/*m_jointAngles[node->name]*/, node->data.jointData.axis );
		cumWorldTransform = cumWorldTransform * _jointTransform;
        // update by the local shape's transform
        glm::mat4 _nodeWorldTransform = cumWorldTransform * node->data.drawData.localTransform;

		glm::vec3 _nodePos = _nodeWorldTransform[3];
		glm::mat4 _nodeRot = glm::mat4( glm::mat3( _nodeWorldTransform ) );

		_nodeMesh->pos		= TVec3( _nodePos.x, _nodePos.y, _nodePos.z );
		_nodeMesh->rotation = _nodeRot;

		for ( int q = 0; q < node->children.size(); q++ )
		{
			_setNodeTransform( node->children[q], cumWorldTransform );
		}
	}

    void TSimCharacterGraphicsComponent::update( float dt )
    {
		//for ( auto _keypair : m_jointAngles )
		//{
		//	m_jointAngles[_keypair.first] += 0.1 * dt;
		//}


    	// For testing only - TODO: Separate this two types of behaviors
    	if ( m_usesMotion )
    	{
	       	reinterpret_cast< TSimCharacterEntity* >( m_parent )->getPose( m_pose );

			auto _rootNode = m_characterTree;
			glm::mat4 _baseWorldTransform( 1.0f );
			_baseWorldTransform = m_parent->rotation * _baseWorldTransform;
			_baseWorldTransform = glm::translate( glm::vec3( m_parent->pos.x,
															 m_parent->pos.y,
															 m_parent->pos.z ) ) * _baseWorldTransform;

			_setNodeTransform( _rootNode, _baseWorldTransform );
    	}
    	else
    	{
			for ( auto& _keypair : m_bodyMeshes )
			{
				_setSingleBodyTransform( _keypair.second, 
										 m_characterRef->getBodyComponentTransform( _keypair.first ) );
			}
    	}
    }

	void TSimCharacterGraphicsComponent::_setSingleBodyTransform( engine::LMesh* pMesh, glm::mat4 pWorldTransform )
	{
		glm::vec3 _pos = pWorldTransform[3];
		glm::mat4 _rot = glm::mat4( glm::mat3( pWorldTransform ) );

		pMesh->pos		= TVec3( _pos.x, _pos.y, _pos.z );
		pMesh->rotation = _rot;
	}

    vector< engine::LMesh* > TSimCharacterGraphicsComponent::getRenderables()
    {
        vector< engine::LMesh* > _renderables;

        for ( auto _pair : m_bodyMeshes )
        {
            _renderables.push_back( _pair.second );
        }

        return _renderables;
    }

}