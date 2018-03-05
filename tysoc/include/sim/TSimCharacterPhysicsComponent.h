
#pragma once

#include <TComponent.h>
#include <utils/TCharacterParser.h>
#include <sim/TSimCharacterEntity.h>
#include <sim/TSimJoint.h>

using namespace std;

namespace tysoc
{

    class TSimCharacterEntity;

    class TSimCharacterPhysicsComponent : public TComponent
    {

        private :

        unordered_map< string, btRigidBody* > m_bodiesMap;
		unordered_map< int, string > m_directDictionary;
		unordered_map< string, int > m_reverseDictionary;
		vector< TSimJoint* > m_joints;

        TCharacterNode* m_characterTree;

		int m_numDof;

        void _buildBody( TCharacterNode* node, glm::mat4 cumTransform );
        void _buildBodiesFromTree();

		void _buildJoint( TCharacterNode* node, glm::mat4 cumTransform );
		void _buildJointsFromTree();

        public :

        TSimCharacterPhysicsComponent( TSimCharacterEntity* pParent, TCharacterNode* tree );
        ~TSimCharacterPhysicsComponent();

        static string getStaticType() { return string( "ragdoll" ); }

        void update( float dt ) override;

		vector< TSimJoint* > getJoints() { return m_joints; }
    };




}