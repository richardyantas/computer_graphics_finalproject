
#include <TPrimitiveGraphicsComponent.h>

using namespace std;

namespace tysoc
{


    TPrimitiveGraphicsComponent::TPrimitiveGraphicsComponent( TEntity* pParent,
                                                              _primitiveGraphicsType primitiveType,
                                                              const TPrimitiveGraphicsParams& params )
        : TGraphicsComponent( pParent )
    {
        
        _buildPrimitive( primitiveType, params );
    }

    void TPrimitiveGraphicsComponent::_buildPrimitive( _primitiveGraphicsType primitiveType, 
                                                       const TPrimitiveGraphicsParams& params )
    {
        engine::LMesh* _mesh = NULL;

        switch ( primitiveType )
        {

            case GRAPHICS_SPHERE :

                _mesh = engine::LMeshBuilder::createSphere( params.sphere_radius );

                break;

            case GRAPHICS_BOX :

                _mesh = engine::LMeshBuilder::createBox( params.box_width,
                                                         params.box_height,
                                                         params.box_depth );

                break;

            case GRAPHICS_CYLINDER :

                _mesh = engine::LMeshBuilder::createCylinder( params.cylinder_baseRadius,
                                                              params.cylinder_length );

                break;

            case GRAPHICS_CAPSULE :

                _mesh = engine::LMeshBuilder::createCapsule( params.capsule_baseRadius,
                                                             params.capsule_length );

                break;
        }

        setRenderable( _mesh );
    }

    TPrimitiveGraphicsComponent::~TPrimitiveGraphicsComponent()
    {
        assert( m_renderable != NULL );

        delete m_renderable;
        m_renderable = NULL;
    }

}
