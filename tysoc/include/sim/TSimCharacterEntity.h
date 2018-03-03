
#pragma once

#include <TEntity.h>
// #include <TSimCharacterGraphicsComponent.h>
// #include <TSimCharacterPhysicsComponent.h>
#include <utils/TCharacterParser.h>

using namespace std;

namespace tysoc
{

    // class TSimCharacterGraphicsComponent;
    // class TSimCharacterPhysicsComponent;

    class TSimCharacterEntity : public TEntity
    {

        private :

        unordered_map< string, glm::mat4 > m_bodiesTransforms;

        TCharacterNode* m_characterTree;

        public :

        TSimCharacterEntity( const string& structureFile, const TVec3& initialPosition );
        ~TSimCharacterEntity();

        void setBodyComponentTransform( string id, const glm::mat4& transform );
        glm::mat4 getBodyComponentTransform( string id );
    };





}