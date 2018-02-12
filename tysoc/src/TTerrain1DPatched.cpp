
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

        // Add initial section
        _addSection( m_start );
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
        // WIP: update section logic here ...
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

}