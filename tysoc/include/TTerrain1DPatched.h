
#pragma once

#include "TTerrain1D.h"
#include "TTerrain1DPatchVoxels.h"
#include <vector>

using namespace std;

namespace tysoc
{

    class TWorld;

    class TTerrain1DPatched : public TTerrain1D
    {

        private :

        vector< TTerrain1DPatchVoxels* > m_patches;

        void _addSection( engine::LVec3 posStart );

        public :

        TTerrain1DPatched( TWorld* pWorld,
                           engine::LVec3 start       = TERRAIN1D_DEFAULT_START,
                           engine::LVec3 direction   = TERRAIN1D_DEFAULT_DIRECTION,
                           engine::LVec3 up          = TERRAIN1D_DEFAULT_UP );
        ~TTerrain1DPatched();

        static string getStaticType() { return string( "patched" ); }

        void update( float dt ) override;

        vector< TTerrain1DPatchVoxels* > getPatches() { return m_patches; }

    };




}
