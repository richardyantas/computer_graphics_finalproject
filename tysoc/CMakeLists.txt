
message( "Configuring tysoc engine ..." )

include_directories( ${TYSOC_INCLUDE_DIRECTORIES} )
link_directories( ${TYSOC_LIBRARY_DIRECTORIES} )

add_library( tysoc
             src/TApp.cpp
             src/TComponent.cpp
             src/TEntity.cpp
             src/TGraphicsComponent.cpp
             src/TPhysicsComponent.cpp
             src/TBasicGraphicsComponent.cpp
             src/TBasicPhysicsComponent.cpp
             src/TPrimitiveGraphicsComponent.cpp
             src/TPrimitivePhysicsComponent.cpp
             src/TPlayerEntity.cpp
             src/controllers/TKeyboardController.cpp
             src/TPrimitiveEntity.cpp
             src/terrain/TTerrain.cpp
             src/terrain/TTerrain1D.cpp
             src/terrain/TTerrain1DPatched.cpp
             src/terrain/TTerrain1DPatchVoxels.cpp
             src/terrain/TTerrainStaticMeshed.cpp
             src/TWorld.cpp
             src/scenarios/TBaseScenario.cpp
             src/utils/TCharacterParser.cpp
             src/sim/TSimCharacterEntity.cpp
             src/sim/TSimCharacterGraphicsComponent.cpp
             src/sim/TSimCharacterMotionComponent.cpp
             src/sim/TSimCharacterPhysicsComponent.cpp
             src/sim/TSimJoint.cpp
             src/TDebugUI.cpp
             src/TMasterRenderer.cpp
             src/renderers/TEntitiesRenderer.cpp
             src/renderers/TTerrainRenderer.cpp
             src/renderers/TTerrainStaticMeshedRenderer.cpp
             src/renderers/TTerrain1DPatchedRenderer.cpp )

if ( BULLET_FOUND )

target_link_libraries( tysoc
                       gengine
                       ${BULLET_LIBRARIES}
					   cat1UI )

else()

target_link_libraries( tysoc
                       gengine
                       BulletCollision
                       BulletDynamics
                       LinearMath
                       cat1UI )

endif()


message( "Configuring tysoc engine - done" )