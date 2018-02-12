
#pragma once


#include "TCommon.h"
#include "TWorld.h"
#include "TTerrain1DPatchedRenderer.h"


namespace tysoc
{


    class TTerrainRenderer
    {

        private :

        TTerrain1DPatchedRenderer* m_terrain1DPatchedRenderer;

        public :

        TTerrainRenderer();
        ~TTerrainRenderer();

        void prepare( TWorld* pWorld );
        void render();
        void clean();

    };



}