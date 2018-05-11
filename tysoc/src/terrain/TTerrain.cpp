
#include <terrain/TTerrain.h>

using namespace std;


namespace tysoc
{


    TTerrain::TTerrain( TWorld* pWorld )
    {
        m_world = pWorld;
        m_type = TTerrain::getStaticType();
    }

    TTerrain::~TTerrain()
    {
        m_world = NULL;
    }


}