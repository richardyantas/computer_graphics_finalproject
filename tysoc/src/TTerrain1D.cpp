
#include <TTerrain1D.h>





namespace tysoc
{

    TTerrain1D::TTerrain1D( TWorld* pWorld,
                            engine::LVec3 start,
                            engine::LVec3 direction,
                            engine::LVec3 up )
    {
        this->type = TTerrain1D::getStaticType();

        m_world = pWorld;
        m_start = start;
        m_direction = direction;
        m_up = up;

        m_current1DPos = 0.0f;
    }

    TTerrain1D::~TTerrain1D()
    {
        m_world = NULL;
    }

    void TTerrain1D::update( float dt )
    {
        // Override this
    }

}