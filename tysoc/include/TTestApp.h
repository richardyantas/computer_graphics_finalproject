
#pragma once

#include "TApp.h"
#include "TPlayerEntity.h"
#include "TTerrain1DPatched.h"

#include <LFixedCamera3d.h>

using namespace std;

namespace tysoc
{


    class TTestApp : public TApp
    {

        public :


        void init() override
        {
            cout << "initializing testapp" << endl;
            m_world = new TWorld();
            m_world->addEntity( new TPlayerEntity() );
            m_world->setTerrain( new TTerrain1DPatched( m_world ) );
            m_world->addCamera( new engine::LFixedCamera3d( engine::LVec3( 0.0f, 0.0f, 20.0f ),
                                                            engine::LVec3( 0.0f, 0.0f, -20.0f ),
                                                            engine::LVec3( 0.0f, 1.0f, 0.0f ) ),
                                "mainCamera" );
            cout << "done initializing testapp" << endl;
        }


    };






}