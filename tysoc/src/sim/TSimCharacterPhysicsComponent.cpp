
#include <sim/TSimCharacterPhysicsComponent.h>



using namespace std;

namespace tysoc
{


    TSimCharacterPhysicsComponent::TSimCharacterPhysicsComponent( TSimCharacterEntity* pParent, TCharacterNode* tree )
        : TPhysicsComponent( pParent )
    {
        m_characterTree = tree;
        this->type = TSimCharacterPhysicsComponent::getStaticType();

		m_characterRef = pParent;

		m_numDof = 0;
		_buildBodiesFromTree();
		_buildJointsFromTree();
    }

    TSimCharacterPhysicsComponent::~TSimCharacterPhysicsComponent()
    {
		m_characterTree = NULL;
		m_characterRef = NULL; 
		
		for ( auto& keypair : m_bodiesMap )
		{
			delete keypair.second;
		}

		m_bodiesMap.clear();
    }

	void TSimCharacterPhysicsComponent::_buildBodiesFromTree()
	{
		glm::mat4 _worldTransform = m_parent->rotation;
		_worldTransform[3] = glm::vec4( m_parent->pos.x, m_parent->pos.y, m_parent->pos.z, 1.0f );

		_buildBody( m_characterTree, _worldTransform );
	}

    void TSimCharacterPhysicsComponent::_buildBody( TCharacterNode* node, glm::mat4 cumTransform )
    {
        m_numDof++;

		auto& _nodeData  = node->data;
		auto& _jointData = _nodeData.jointData;
		auto& _bodyData  = _nodeData.shapeData;

		btCollisionShape* _rbShape = NULL;

		switch ( g_CollisionShapeMap[_bodyData.shape] )
		{
			case COLLISION_BOX :

				_rbShape = new btBoxShape( btVector3( WORLD_SCALE * _bodyData.param0 / 2,
													  WORLD_SCALE * _bodyData.param1 / 2,
													  WORLD_SCALE * _bodyData.param2 / 2 ) );

				break;

			default:
				cout << "btype: " << _bodyData.shape << " is not supported" << endl;
				break;
		}

		if ( _rbShape != NULL )
		{
			cumTransform = _jointData.localTransform * cumTransform;

			glm::mat4 _worldTransform = _bodyData.localTransform * cumTransform;

			glm::vec3 _nodePos = _worldTransform[3];
			glm::mat4 _nodeRot = glm::mat4( glm::mat3( _worldTransform ) );

			glm::quat _qOrientation = glm::quat_cast( _nodeRot );

			btTransform _rbTransform;
			_rbTransform.setIdentity();
			_rbTransform.setOrigin( btVector3( _nodePos.x, _nodePos.y, _nodePos.z ) );
			_rbTransform.setRotation( btQuaternion( _qOrientation.x,
													_qOrientation.y,
													_qOrientation.z,
													_qOrientation.w ) );

			btDefaultMotionState* _rbMotionState = new btDefaultMotionState( _rbTransform );

			btScalar _rbMass = _bodyData.mass;

			btVector3 _rbInertia( 0, 0, 0 );
			if ( _rbMass != 0.0f )
			{
				_rbShape->calculateLocalInertia( _rbMass, _rbInertia );
			}

			btRigidBody::btRigidBodyConstructionInfo _rbConstructionInfo( _rbMass,
																		  _rbMotionState,
																		  _rbShape,
																		  _rbInertia );

			btRigidBody* _rbBody = new btRigidBody( _rbConstructionInfo );
			_rbBody->setRestitution( 0.5 );

			m_bodiesMap[node->name] = _rbBody;
			m_directDictionary[node->id] = node->name;
			m_reverseDictionary[node->name] = node->id;
		}


		for ( int q = 0; q < node->children.size(); q++ )
		{
			_buildBody( node->children[q], cumTransform );
		}
    }

	void TSimCharacterPhysicsComponent::_buildJointsFromTree()
	{
		_buildJoint( m_characterTree, glm::mat4( 1.0f ) );
	}

	void TSimCharacterPhysicsComponent::_buildJoint( TCharacterNode* node, glm::mat4 cumTransform )
	{
		auto& _jointData = node->data.jointData;

		if ( _jointData.parentId != -1 )
		{
			// It's attached to a parent body by a constraint
			if ( _jointData.jointType == TSimJoint::JOINT_TYPE_REVOLUTE )
			{
				auto _parentName = m_directDictionary[_jointData.parentId];
				auto _childName = m_directDictionary[node->id];

				auto _parentBody = m_bodiesMap[_parentName];
				auto _childBody = m_bodiesMap[_childName];

				auto _simJoint = new TSimJoint( _parentBody, _parentName,
												_childBody, _childName,
												_jointData.pivot, _jointData.axis,
											    _jointData.loLimit, _jointData.hiLimit );
				m_joints.push_back( _simJoint );
			}
		}

		for ( int q = 0; q < node->children.size(); q++ )
		{
			_buildJoint( node->children[q], cumTransform );
		}
	}

    void TSimCharacterPhysicsComponent::update( float dt )
    {
		for ( auto& _keypair : m_bodiesMap )
		{
			_updateBody( _keypair.second, _keypair.first );
		}

		//auto _simParentEntity = reinterpret_cast< TSimCharacterEntity* >( m_parent );

  //      vector< float > _poseEntity( _simParentEntity->numDof(), 0.0f );

  //      _simParentEntity->setPose( _poseEntity );
    }

	void TSimCharacterPhysicsComponent::_updateBody( btRigidBody* body, string name )
	{
		btTransform _transform;
		body->getMotionState()->getWorldTransform( _transform );

		btVector3 _position = _transform.getOrigin();
		btQuaternion _rotation = _transform.getRotation();

		glm::vec3 _pos( _position.x(), _position.y(), _position.z() );
		glm::quat _rotQuat( _rotation.w(), _rotation.x(), _rotation.y(), _rotation.z() );
		glm::mat4 _rotMat = glm::mat4_cast( _rotQuat );

		glm::mat4 _bTransform = _rotMat;
		_bTransform[3] = glm::vec4( _pos, 1.0f );

		m_characterRef->setBodyComponentTransform( name, _bTransform );
	}
}