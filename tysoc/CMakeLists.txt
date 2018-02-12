
message( "Configuring tysoc engine ..." )

include_directories( ../gengine/include include/ ${BULLET_INCLUDE_DIRS} )

add_library( tysoc
             src/TApp.cpp
             src/TComponent.cpp
             src/TEntity.cpp
             src/TGraphicsComponent.cpp
             src/TPhysicsComponent.cpp
             src/TBasicGraphicsComponent.cpp
             src/TBasicPhysicsComponent.cpp
             src/TPlayerEntity.cpp
             src/TTerrain1D.cpp
             src/TTerrain1DPatched.cpp
             src/TTerrain1DPatchVoxels.cpp
             src/TWorld.cpp
             src/TMasterRenderer.cpp
             src/TEntitiesRenderer.cpp
             src/TTerrainRenderer.cpp
             src/TTerrain1DPatchedRenderer.cpp )

target_link_libraries( tysoc
                       gengine
                       BulletCollision
                       BulletDynamics
                       LinearMath )

message( "Configuring tysoc engine - done" )