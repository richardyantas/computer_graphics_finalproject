
#pragma once

#include "TGraphicsComponent.h"
#include <LMesh.h>
#include <LMeshBuilder.h>

using namespace std;

namespace tysoc
{

    struct TPrimitiveGraphicsParams
    {
        // sphere params
        float sphere_radius;

        // box params
        float box_width;
        float box_height;
        float box_depth;

        // cylinder params
        float cylinder_baseRadius;
        float cylinder_length;

        // capsule params
        float capsule_baseRadius;
        float capsule_length;
    };

    class TPrimitiveGraphicsComponent : public TGraphicsComponent
    {
        private :

        void _buildPrimitive( _primitiveGraphicsType primitiveType, 
                              const TPrimitiveGraphicsParams& params );

        public :

        TPrimitiveGraphicsComponent( TEntity* pParent,
                                     _primitiveGraphicsType primitiveType,
                                     const TPrimitiveGraphicsParams& params );

        ~TPrimitiveGraphicsComponent();

        static string getStaticType() { return string( "baseGraphics" ); }

    };





}