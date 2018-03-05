
#pragma once

#include <TComponent.h>
#include <utils/TCharacterParser.h>
#include <sim/TSimCharacterEntity.h>

using namespace std;

namespace tysoc
{

    class TSimCharacterEntity;

    class TSimCharacterMotionComponent : public TComponent
    {

        private :

        vector< TMotionFrame > m_motionFrames;
        vector< float > m_currentPose;
        vector< float > m_durationBuckets;

		float m_motionTimer;
        float m_motionDuration;
		int m_currentIndx;

        void _blendPose( int indxPoseStart, int indxPoseEnd, float alpha );
        void _getPoseIndx( float time, int& indxPoseStart, float& alpha );

        public :

        TSimCharacterMotionComponent( TSimCharacterEntity* pParent, const string& filename );
        ~TSimCharacterMotionComponent();

        static string getStaticType() { return string( "motion" ); }

        void getPose( vector< float >& pose );

        void update( float dt ) override;
    };




}