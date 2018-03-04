
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

        void _buildNode( TCharacterNode* node, glm::mat4 cumTransform );
        void _buildFromTree();

		void _setNodeTransform( TCharacterNode* node, 
								glm::mat4 cumLocalTransform, 
								const glm::mat4& baseWorldTransform );

        public :

        TSimCharacterGraphicsComponent( TSimCharacterEntity* pParent, TCharacterNode* tree );
        ~TSimCharacterGraphicsComponent();

        static string getStaticType() { return string( "skeletal" ); }

        void update( float dt ) override;

        vector< engine::LMesh* > getRenderables();
    };




}