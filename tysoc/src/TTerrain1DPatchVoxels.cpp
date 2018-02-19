
#include "TTerrain1DPatchVoxels.h"

namespace tysoc
{


    TTerrain1DPatchVoxels::TTerrain1DPatchVoxels( engine::LVec3 start,
                                                  engine::LVec3 direction,
                                                  engine::LVec3 up,
                                                  float pMinLength, float pMaxLength, float pDepth,
                                                  float pMinHeight, float pMaxHeight, 
                                                  int minBumps, int maxBumps )
    {
        m_start = start;
        m_direction = direction;
        m_up = up;

        // build params from random ranges
        m_numBumps = _RAND_INT_RANGE( minBumps, maxBumps );

        float _length = _RAND_FLOAT_RANGE( pMinLength, pMaxLength );
        float _dlength = _length / m_numBumps;

        for ( int q = 0; q < m_numBumps; q++ )
        {
            m_bumpsPos.push_back( ( q + 0.5 ) * _dlength );
            m_bumpsHeight.push_back( _RAND_FLOAT_RANGE( pMinHeight, pMaxHeight ) );
        }

        // build geometry
        for ( int q = 0; q < m_numBumps; q++ )
        {
            TBoxVoxelInfo _bInfo;
            _bInfo.center = engine::LVec3( m_start.x + m_bumpsPos[q] * m_direction.x + m_bumpsHeight[q] * m_up.x,
                                           m_start.y + m_bumpsPos[q] * m_direction.y + m_bumpsHeight[q] * m_up.y,
                                           m_start.z + m_bumpsPos[q] * m_direction.z + m_bumpsHeight[q] * m_up.z );
            _bInfo.size = engine::LVec3( _dlength, m_bumpsHeight[q], pDepth );
            _bInfo.direction = m_direction;
            _bInfo.up = m_up;

            _buildBoxVoxel( _bInfo );
        }
    }


    TTerrain1DPatchVoxels::~TTerrain1DPatchVoxels()
    {
        // TODO: implemented this
    }

    void TTerrain1DPatchVoxels::_buildBoxVoxel( const TBoxVoxelInfo& boxVoxelInfo )
    {
        // Build the mesh
        auto _xAxis = boxVoxelInfo.direction;
        auto _yAxis = boxVoxelInfo.up;
        auto _zAxis = engine::LVec3::cross( _xAxis, _yAxis );

        auto _box = engine::LMeshBuilder::createBox( boxVoxelInfo.size.x,
                                                     boxVoxelInfo.size.y,
                                                     boxVoxelInfo.size.z );
        _box->rotation = glm::mat4( glm::vec4( _xAxis.x, _xAxis.y, _xAxis.z, 0.0f ), 
                                    glm::vec4( _yAxis.x, _yAxis.y, _yAxis.z, 0.0f ), 
                                    glm::vec4( _zAxis.x, _zAxis.y, _zAxis.z, 0.0f ), 
                                    glm::vec4( glm::vec3( 0.0f ), 1.0f ) );
        _box->pos = boxVoxelInfo.center;

        m_gVoxels.push_back( _box );

        // Build the rigid body
        btTransform _rbTransform;
        _rbTransform.setIdentity();
        _rbTransform.setOrigin( btVector3( boxVoxelInfo.center.x, 
                                           boxVoxelInfo.center.y,
                                           boxVoxelInfo.center.z ) );
        glm::quat _qOrientation = glm::quat_cast( glm::mat3( glm::vec3( _xAxis.x, _xAxis.y, _xAxis.z ), 
                                                             glm::vec3( _yAxis.x, _yAxis.y, _yAxis.z ), 
                                                             glm::vec3( _zAxis.x, _zAxis.y, _zAxis.z ) ) );
        _rbTransform.setRotation( btQuaternion( _qOrientation.x, 
                                                _qOrientation.y,
                                                _qOrientation.z,
                                                _qOrientation.w ) );

        auto _rbShape = new btBoxShape( btVector3( boxVoxelInfo.size.x / 2,
                                                   boxVoxelInfo.size.y / 2,
                                                   boxVoxelInfo.size.z / 2 ) );
        auto _rbMotionState = new btDefaultMotionState( _rbTransform );
        btRigidBody::btRigidBodyConstructionInfo _rbConstructionInfo( 0.0, _rbMotionState, _rbShape, btVector3( 0, 0, 0 ) );
        auto _rbBody = new btRigidBody( _rbConstructionInfo );
        _rbBody->setRestitution( 1.0f );

        m_pVoxels.push_back( _rbBody );
    }


}