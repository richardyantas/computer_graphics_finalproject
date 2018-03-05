
#include <sim/TSimCharacterMotionComponent.h>



using namespace std;

namespace tysoc
{


    TSimCharacterMotionComponent::TSimCharacterMotionComponent( TSimCharacterEntity* pParent, const string& filename )
        : TComponent( pParent )
    {
        
        TCharacterParser::parseMotion( m_motionFrames, "raptor_run.json" );

        this->type = TSimCharacterMotionComponent::getStaticType();
        
        m_currentPose = vector< float >( m_motionFrames[0].dof );

		m_motionTimer = 0.0f;
		m_currentIndx = 0;
        m_motionDuration = 0.0f;
        m_durationBuckets = vector< float >( m_motionFrames.size() + 1, 0.0f );

        //for ( int q = 0; q < m_motionFrames.size(); q++ )
        //{
        //    m_motionDuration += m_motionFrames[q].duration;
        //}

        //for ( int q = 1; q <= m_motionFrames.size(); q++ )
        //{
        //    m_durationBuckets[q] = m_motionFrames[ q - 1 ].duration + m_durationBuckets[ q - 1 ];
        //}

		m_durationBuckets = { 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 3.5f };
		m_motionDuration = m_durationBuckets.back();
    }

    TSimCharacterMotionComponent::~TSimCharacterMotionComponent()
    {
		m_motionFrames.clear();
    }



    void TSimCharacterMotionComponent::update( float dt )
    {
		m_motionTimer += dt;
		
        int _indxPoseStart;
        float _blendAlpha;

        _getPoseIndx( m_motionTimer, _indxPoseStart, _blendAlpha );
        _blendPose( _indxPoseStart, _indxPoseStart + 1, _blendAlpha );

        auto _simParentEntity = reinterpret_cast< TSimCharacterEntity* >( m_parent );

        if ( m_currentPose.size() - _simParentEntity->numDof() != 3 )
        {
            cout << "dimension mismatch - entity.pose.size: " << _simParentEntity->numDof() << " - motion.pose.size: " << m_currentPose.size() << endl;
            return;
        }

        vector< float > _poseEntity( _simParentEntity->numDof(), 0.0f );

        for ( int q = 0; q < _poseEntity.size(); q++ )
        {
            _poseEntity[q] = m_currentPose[q + 3];
        }

        _simParentEntity->setPose( _poseEntity );
    }


    void TSimCharacterMotionComponent::getPose( vector< float >& pose )
    {
        pose = m_currentPose;
    }

    void TSimCharacterMotionComponent::_blendPose( int indxPoseStart, int indxPoseEnd, float alpha )
    {
        TMotionFrame& _frameStart = m_motionFrames[indxPoseStart];
        TMotionFrame& _frameEnd   = m_motionFrames[indxPoseEnd % m_motionFrames.size()];

        for ( int q = 0; q < m_currentPose.size(); q++ )
        {
            m_currentPose[q] = ( 1 - alpha ) * _frameStart.pose[q] + ( alpha ) * _frameEnd.pose[q];
        }
    }
    
    void TSimCharacterMotionComponent::_getPoseIndx( float time, int& indxPoseStart, float& alpha )
    {
        float _normalizedTime = std::fmod( time, m_motionDuration );
        _normalizedTime = ( _normalizedTime < 0 ) ? ( _normalizedTime + m_motionDuration ) : _normalizedTime;

        auto _it = std::upper_bound( m_durationBuckets.begin(), m_durationBuckets.end(), _normalizedTime );
        indxPoseStart = static_cast< int >( _it - m_durationBuckets.begin() - 1 );

        float _time0 = m_durationBuckets[ indxPoseStart ];
        float _time1 = m_durationBuckets[ indxPoseStart + 1 ];

        alpha = ( _normalizedTime - _time0 ) / ( _time1 - _time0 );
    }
}