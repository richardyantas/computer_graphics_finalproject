
#pragma once

#include <TEntity.h>
#include <sim/TSimCharacterGraphicsComponent.h>
#include <sim/TSimCharacterMotionComponent.h>
#include <sim/TSimCharacterPhysicsComponent.h>
#include <utils/TCharacterParser.h>

using namespace std;

namespace tysoc
{

    class TSimCharacterGraphicsComponent;
    class TSimCharacterPhysicsComponent;

    class TSimCharacterEntity : public TEntity
    {

        private :

        unordered_map< string, glm::mat4 > m_bodiesTransforms;

        TCharacterNode* m_characterTree;
        // Joints variables
        vector< float > m_pose;

        // number of degrees of freedom
        int m_numDof;

        public :

        TSimCharacterEntity( const string& structureFile, const TVec3& initialPosition, bool useFramesMotion = false );
        ~TSimCharacterEntity();

        void setBodyComponentTransform( string id, const glm::mat4& transform );
        glm::mat4 getBodyComponentTransform( string id );

        void setPose( const vector< float >& pose );
        void getPose( vector< float >& pose );

        int numDof() { return m_numDof; }
    };





}