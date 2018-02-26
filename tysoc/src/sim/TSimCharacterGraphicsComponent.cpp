
#include <sim/TSimCharacterGraphicsComponent.h>



using namespace std;

namespace tysoc
{


    TSimCharacterGraphicsComponent::TSimCharacterGraphicsComponent( TSimCharacterEntity* pParent, TCharacterNode* tree )
        : TEntity( pParent )
    {
        m_characterTree = tree;

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

        m_bodyMeshes[ node->name ] = _mesh;
    }


    void TSimCharacterGraphicsComponent::update( float dt )
    {

    }

    vector< engine::LMesh* > getRenderables()
    {
        vector< engine:.LMesh* > _renderables;

        for ( auto _pair : m_bodyMeshes )
        {
            _renderables.push_back( _pair.second );
        }

        return _renderables;
    }

}