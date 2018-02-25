
#include <TTerrain1DPatched.h>



namespace tysoc
{


    TTerrain1DPatched::TTerrain1DPatched( TWorld* pWorld,
                                          engine::LVec3 start,
                                          engine::LVec3 direction,
                                          engine::LVec3 up )
        : TTerrain1D( pWorld, start, direction, up )
    {
        this->type = TTerrain1DPatched::getStaticType();

        m_fcameras = m_world->getCamerasByType< engine::LFixedCamera3d >();

        // Do initial calculation of the view ranges
        computeBoxRangeFromCameras( m_fcameras );
        // Add initial section
        auto _frontLimit = m_cameraRangeMovementAxes.p[2].x;
        
        while( m_current1DPos < _frontLimit )
        {
            auto _posStart = m_start;
            _posStart.x += m_current1DPos * m_direction.x;
            _posStart.y += m_current1DPos * m_direction.y;
            _posStart.z += m_current1DPos * m_direction.z;
            
            _addSection( _posStart );
        }
    }

    TTerrain1DPatched::~TTerrain1DPatched()
    {
        for ( auto _patch : m_patches )
        {
            delete _patch;
        }

        m_patches.clear();
    }

    void TTerrain1DPatched::update( float dt )
    {
        computeBoxRangeFromCameras( m_fcameras );

        auto _frontLimit = m_cameraRangeMovementAxes.p[2].x;

        while( m_current1DPos < _frontLimit )
        {
            auto _posStart = m_start;
            _posStart.x += m_current1DPos * m_direction.x;
            _posStart.y += m_current1DPos * m_direction.y;
            _posStart.z += m_current1DPos * m_direction.z;

            _addSection( _posStart );
        }
    }

    void TTerrain1DPatched::_addSection( engine::LVec3 posStart )
    {
        auto _patch = new TTerrain1DPatchVoxels( posStart,
                                                 m_direction,
                                                 m_up );

        m_patches.push_back( _patch );

        m_current1DPos += _patch->patchLength() + 1.0f;

        // add rigidbodies to the world
        auto _btWorld = m_world->getBulletWorld();
        auto _rbodies = _patch->getVoxelsPhysics();
        
        for ( auto _rbody : _rbodies )
        {
            _btWorld->addRigidBody( _rbody );
        }
            
    }

    void TTerrain1DPatched::setMaterial( const engine::LVec3& ambient,
                                         const engine::LVec3& diffuse,
                                         const engine::LVec3& specular,
                                         float shininess )
    {
        for ( auto _patch : m_patches )
        {
            _patch->setMaterial( ambient, diffuse, specular, shininess );
        }
    }

}