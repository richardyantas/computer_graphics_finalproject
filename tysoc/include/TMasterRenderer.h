
#pragma once

#include "TWorld.h"
#include "TTerrainRenderer.h"
#include "TEntitiesRenderer.h"

#include <LShadowMap.h>
#include <LLightDirectional.h>



namespace tysoc
{


    class TMasterRenderer
    {
        private :

        TTerrainRenderer* m_terrainRenderer;
        TEntitiesRenderer* m_entitiesRenderer;

        bool m_drawAsWireframe;
        bool m_drawShadows;

        engine::LShadowMap* m_shadowMap;
        engine::LLightDirectional* m_lightRef;

        public :

        TMasterRenderer();
        ~TMasterRenderer();

        void prepare( TWorld* pWorld );
        void render();
        void clean();

        void enableWireframe() { m_drawAsWireframe = true; }
        void disableWireframe() { m_drawAsWireframe = false; }

        void enableShadows() { m_drawShadows = true; }
        void disableShadows() { m_drawShadows = false; }

        bool areShadowsEnabled() { return m_drawShadows; }

    };





}