
#pragma once

#include <TGraphicsComponent.h>
#include <LMesh.h>
#include <LMeshBuilder.h>
#include <utils/TCharacterParser.h>
#include <sim/TSimCharacterEntity.h>

using namespace std;

namespace tysoc
{

    class TSimCharacterEntity;

    class TSimCharacterGraphicsComponent : public TGraphicsComponent
    {

        private :

        unordered_map< string, engine::LMesh* > m_bodyMeshes;

        TCharacterNode* m_characterTree;
		TSimCharacterEntity* m_characterRef;

        int m_numDof;

        void _buildNode( TCharacterNode* node, glm::mat4 cumTransform );
        void _buildFromTree();

		void _setNodeTransform( TCharacterNode* node, 
								glm::mat4 cumWorldTransform );

		void _setSingleBodyTransform( engine::LMesh* pMesh, glm::mat4 pWorldTransform );

		unordered_map< string, float > m_jointAngles;
        vector< float > m_pose;

        public :

        TSimCharacterGraphicsComponent( TSimCharacterEntity* pParent, TCharacterNode* tree );
        ~TSimCharacterGraphicsComponent();

        static string getStaticType() { return string( "skeletal" ); }

        void update( float dt ) override;

        int getNumDof() { return m_numDof; }
        vector< engine::LMesh* > getRenderables();
    };




}