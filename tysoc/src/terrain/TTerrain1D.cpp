
#include <terrain/TTerrain1D.h>


using namespace std;

namespace tysoc
{

    TTerrain1D::TTerrain1D( TWorld* pWorld,
                            engine::LVec3 start,
                            engine::LVec3 direction,
                            engine::LVec3 up )
        : TTerrain( pWorld )
    {
        m_type = TTerrain1D::getStaticType();

        m_start = start;
        m_direction = direction;
        m_up = up;
        m_side = engine::LVec3::cross( m_direction, m_up );

        m_current1DPos = m_start.x * m_direction.x;
    }

    TTerrain1D::~TTerrain1D()
    {
        m_world = NULL;
    }

    void TTerrain1D::update( float dt )
    {
        // Override this
    }

    void TTerrain1D::setMaterial( const engine::LVec3& ambient,
                                  const engine::LVec3& diffuse,
                                  const engine::LVec3& specular,
                                  float shininess )
    {
        // Override this
    }

    void TTerrain1D::computeBoxRangeFromCameras( const vector< engine::LFixedCamera3d* >& vCameras )
    {
        // do calculations respect to up view
        vector< TAABB > _boxBoundaries;

        for ( auto _camera : vCameras )
        {
            _boxBoundaries.push_back( _computeRangeFromCamera( _camera ) );
        }

        // get the whole range area from all the bounding boxes
        float _fMin = _boxBoundaries[0].p[0].x;
        float _fMax = _boxBoundaries[0].p[2].x;
        float _sMin = _boxBoundaries[0].p[1].y;
        float _sMax = _boxBoundaries[0].p[3].y;

        for ( int q = 1; q < _boxBoundaries.size(); q++ )
        {
            _fMin = min( _fMin, _boxBoundaries[q].p[0].x );
            _fMax = max( _fMax, _boxBoundaries[q].p[2].x );
            _sMin = min( _sMin, _boxBoundaries[q].p[1].y );
            _sMax = max( _sMax, _boxBoundaries[q].p[3].y );
        }

        m_cameraRangeMovementAxes.p[0] = engine::LVec2( _fMin, _sMax );// near
        m_cameraRangeMovementAxes.p[1] = engine::LVec2( _fMin, _sMin );// near
        m_cameraRangeMovementAxes.p[2] = engine::LVec2( _fMax, _sMin );// far
        m_cameraRangeMovementAxes.p[3] = engine::LVec2( _fMax, _sMax );// far

        // rotation matrix is ...
        //      | m_direction.x ,  m_side.x |
        //      | m_direction.z ,  m_side.z |

        for ( int q = 0; q < 4; q++ )
        {
            engine::LVec2 _original, _transformed;

            _original = m_cameraRangeMovementAxes.p[q];
            _transformed.x = m_direction.x * _original.x + m_side.x * _original.y;
            _transformed.y = m_direction.z * _original.x + m_side.z * _original.y;

            m_cameraRangeWorldAxes.p[q] = _transformed;
        }
    }

    TAABB TTerrain1D::_computeRangeFromCamera( engine::LFixedCamera3d* pCamera )
    {
        glm::mat4 _viewMatrix = pCamera->getViewMatrix();
        glm::mat4 _projMatrix = pCamera->getProjectionMatrix();

        glm::mat4 _clipMatrix = _projMatrix * _viewMatrix;
        glm::mat4 _invClipMatrix = glm::inverse( _clipMatrix );

        #define FRUSTUM_NUM_POINTS 8

        glm::vec3 _frustumPointsClipSpace[ FRUSTUM_NUM_POINTS ] = {
            // near plane
            { -1.0f, -1.0f, -1.0f },{ 1.0f, -1.0f, -1.0f },
            { 1.0f,  1.0f, -1.0f },{ -1.0f,  1.0f, -1.0f },
            // far plane
            { -1.0f, -1.0f,  1.0f },{ 1.0f, -1.0f,  1.0f },
            { 1.0f,  1.0f,  1.0f },{ -1.0f,  1.0f,  1.0f }
        };

        vector< engine::LVec3 > _points3d;

        for ( int q = 0; q < FRUSTUM_NUM_POINTS; q++ )
        {
            glm::vec4 _pointFrustum = _invClipMatrix * glm::vec4( _frustumPointsClipSpace[q], 1.0f );
            glm::vec3 _pointFrustumNormalized = glm::vec3( _pointFrustum.x / _pointFrustum.w,
                                                           _pointFrustum.y / _pointFrustum.w,
                                                           _pointFrustum.z / _pointFrustum.w );

            _points3d.push_back( engine::LVec3( _pointFrustumNormalized.x, 
                                                _pointFrustumNormalized.y, 
                                                _pointFrustumNormalized.z ) );
        }

        // Compute component along movement axes

        // Along direction-front vector
        float _frontComp[ FRUSTUM_NUM_POINTS ];
        for ( int q = 0; q < FRUSTUM_NUM_POINTS; q++ )
        {
            _frontComp[q] = engine::LVec3::dot( _points3d[q], m_direction );
        }

        // Along side-right vector
        float _sideComp[ FRUSTUM_NUM_POINTS ];
        for ( int q = 0; q < FRUSTUM_NUM_POINTS; q++ )
        {
            _sideComp[q] = engine::LVec3::dot( _points3d[q], m_side );
        }

        // Compute bounding box along movement axes

        float _fMin = _frontComp[0];
        float _fMax = _frontComp[0];
        float _sMin = _sideComp[0];
        float _sMax = _sideComp[0];

        for ( int q = 1; q < FRUSTUM_NUM_POINTS; q++ )
        {
            _fMin = min( _fMin, _frontComp[q] );
            _fMax = max( _fMax, _frontComp[q] );

            _sMin = min( _sMin, _sideComp[q] );
            _sMax = max( _sMax, _sideComp[q] );
        }

        TAABB _cameraRangeMovementAxes;

        _cameraRangeMovementAxes.p[0] = engine::LVec2( _fMin, _sMax );// near
        _cameraRangeMovementAxes.p[1] = engine::LVec2( _fMin, _sMin );// near
        _cameraRangeMovementAxes.p[2] = engine::LVec2( _fMax, _sMin );// far
        _cameraRangeMovementAxes.p[3] = engine::LVec2( _fMax, _sMax );// far

        return _cameraRangeMovementAxes;
    }
}