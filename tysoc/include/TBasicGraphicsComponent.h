
#pragma once

#include "TGraphicsComponent.h"
#include <LMesh.h>
#include <LMeshBuilder.h>

using namespace std;

namespace tysoc
{



    class TBasicGraphicsComponent : public TGraphicsComponent
    {

        public :

        TBasicGraphicsComponent( TEntity* pParent );
        TBasicGraphicsComponent( TEntity* pParent, engine::LMesh* pMesh );
        ~TBasicGraphicsComponent();

        static string getStaticType() { return string( "basicGraphics" ); }

    };





}