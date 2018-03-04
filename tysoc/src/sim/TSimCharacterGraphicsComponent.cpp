
#include <sim/TSimCharacterGraphicsComponent.h>



using namespace std;

namespace tysoc
{


    TSimCharacterGraphicsComponent::TSimCharacterGraphicsComponent( TSimCharacterEntity* pParent, TCharacterNode* tree )
        : TGraphicsComponent( pParent )
    {
        m_characterTree = tree;
		this->type = TSimCharacterGraphicsComponent::getStaticType();
        _buildFromTree();
    }

    TSimCharacterGraphicsComponent::~TSimCharacterGraphicsComponent()
    {
        m_characterTree = NULL;
    }

    void TSimCharacterGraphicsComponent::_buildFromTree()
    {
        _buildNode( m_characterTree, glm::mat4( 1.0f ) );
    }

    void TSimCharacterGraphicsComponent::_buildNode( TCharacterNode* node, glm::mat4 cumTransform )
    {
        auto& _nodeData = node->data;
        auto& _drawData = _nodeData.drawData;
		auto& _jointData = _nodeData.jointData;

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

			cumTransform = _drawData.localTransform * cumTransform;

			glm::vec3 _pos = cumTransform[3];
			glm::mat3 _rot = glm::mat3( cumTransform );
			_mesh->pos = TVec3( _pos.x, _pos.y, _pos.z );
			_mesh->rotation = glm::mat4( _rot );

			m_bodyMeshes[node->name] = _mesh;
		}


		for ( int q = 0; q < node->children.size(); q++ )
		{
			_buildNode( node->children[q], cumTransform );
		}
    }

	void TSimCharacterGraphicsComponent::_setNodeTransform( TCharacterNode* node,
														   glm::mat4 cumLocalTransform,
														   const glm::mat4& baseWorldTransform )
	{
		auto _nodeMesh = m_bodyMeshes[node->name];

		cumLocalTransform = node->data.drawData.localTransform * cumLocalTransform;

		glm::mat4 _nodeWorldTransform = cumLocalTransform * baseWorldTransform;
		glm::vec3 _nodePos = _nodeWorldTransform[3];
		glm::mat4 _nodeRot = glm::mat4( glm::mat3( _nodeWorldTransform ) );

		_nodeMesh->pos		= TVec3( _nodePos.x, _nodePos.y, _nodePos.z );
		_nodeMesh->rotation = _nodeRot;

		for ( int q = 0; q < node->children.size(); q++ )
		{
			_setNodeTransform( node->children[q], cumLocalTransform, baseWorldTransform );
		}
	}

    void TSimCharacterGraphicsComponent::update( float dt )
    {
		auto _rootNode = m_characterTree;
		glm::mat4 _cumLocalTransform( 1.0f );
		glm::mat4 _baseWorldTransform( 1.0f );
		_baseWorldTransform = m_parent->rotation * _baseWorldTransform;
		_baseWorldTransform = glm::translate( glm::vec3( m_parent->pos.x,
														 m_parent->pos.y,
														 m_parent->pos.z ) ) * _baseWorldTransform;

		_setNodeTransform( _rootNode, _cumLocalTransform, _baseWorldTransform );
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