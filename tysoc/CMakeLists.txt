
message( "Configuring tysoc engine ..." )

include_directories( ${TYSOC_INCLUDE_DIRECTORIES} )
#link_directories( ${TYSOC_LIBRARY_DIRECTORIES} )

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
             src/TTerrain1D.cpp
             src/TTerrain1DPatched.cpp
             src/TTerrain1DPatchVoxels.cpp
             src/TWorld.cpp
             src/scenarios/TBaseScenario.cpp
             src/TDebugUI.cpp
             src/TMasterRenderer.cpp
             src/TEntitiesRenderer.cpp
             src/TTerrainRenderer.cpp
             src/TTerrain1DPatchedRenderer.cpp )

target_link_libraries( tysoc
                       gengine
                       BulletCollision
                       BulletDynamics
                       LinearMath
					   cat1UI )

message( "Configuring tysoc engine - done" )