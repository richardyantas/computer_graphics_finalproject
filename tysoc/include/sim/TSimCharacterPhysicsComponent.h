
#pragma once

#include <TPhysicsComponent.h>
#include <utils/TCharacterParser.h>
#include <sim/TSimCharacterEntity.h>
#include <sim/TSimJoint.h>

using namespace std;

namespace tysoc
{

    class TSimCharacterEntity;

    class TSimCharacterPhysicsComponent : public TPhysicsComponent
    {

        private :

        unordered_map< string, btRigidBody* > m_bodiesMap;
		unordered_map< int, string > m_directDictionary;
		unordered_map< string, int > m_reverseDictionary;
		vector< TSimJoint* > m_joints;

        TCharacterNode* m_characterTree;

		int m_numDof;

		TSimCharacterEntity* m_characterRef;

        void _buildBody( TCharacterNode* node, glm::mat4 cumTransform );
        void _buildBodiesFromTree();

		void _buildJoint( TCharacterNode* node, glm::mat4 cumTransform );
		void _buildJointsFromTree();

        public :

        TSimCharacterPhysicsComponent( TSimCharacterEntity* pParent, TCharacterNode* tree );
        ~TSimCharacterPhysicsComponent();

        static string getStaticType() { return string( "ragdoll" ); }

		void _updateBody( btRigidBody* body, string name );
        void update( float dt ) override;

		unordered_map< string, btRigidBody* > getBodies() { return m_bodiesMap; }
		vector< TSimJoint* > getJoints() { return m_joints; }
    };




}