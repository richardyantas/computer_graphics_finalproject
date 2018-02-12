
#pragma once

#include "TWorld.h"
#include "TTerrain1DPatched.h"
#include <LICamera.h>
#include <LMesh.h>
#include <LShaderManager.h>
#include <LShaderBasic3d.h>

namespace tysoc
{



    class TTerrain1DPatchedRenderer
    {

        private :

        vector< engine::LMesh* > m_renderables;

        engine::LICamera* m_cameraRef;

        public :

        TTerrain1DPatchedRenderer();
        ~TTerrain1DPatchedRenderer();

        void prepare( TWorld* pWorld );
        void render();
        void clean();


    };





}