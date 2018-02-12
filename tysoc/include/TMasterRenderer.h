
#pragma once

#include "TWorld.h"
#include "TTerrainRenderer.h"
#include "TEntitiesRenderer.h"



namespace tysoc
{


    class TMasterRenderer
    {
        private :

        TTerrainRenderer* m_terrainRenderer;
        TEntitiesRenderer* m_entitiesRenderer;

        bool m_drawAsWireframe;

        public :

        TMasterRenderer();
        ~TMasterRenderer();

        void prepare( TWorld* pWorld );
        void render();
        void clean();

        void enableWireframe() { m_drawAsWireframe = true; }
        void disableWireframe() { m_drawAsWireframe = false; }

    };





}