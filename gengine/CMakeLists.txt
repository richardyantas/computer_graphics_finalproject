
message( "Configuring gl engine ..." )

include_directories( include/ )
include_directories( ../ext/glm )
include_directories( ../ext/stb )
include_directories( ../ext/glfw/include )
# include_directories( ../ext/glew/include )

link_directories( /usr/local/lib )

add_library( gengine
             src/LCommon.cpp
             src/LComponent.cpp
             src/LEntity.cpp
             src/LFixedCamera3d.cpp
             src/LFpsCamera.cpp
             src/LInputHandler.cpp
             src/LICamera.cpp
             src/LIndexBuffer.cpp
             src/LTexture.cpp
             src/LCubeTexture.cpp
             src/LSkybox.cpp
             src/LMeshBuilder.cpp
             src/LMeshComponent.cpp
             src/LHeightmapGenerator.cpp
             src/LTerrainPatch.cpp
             src/LMesh.cpp
             src/LScene.cpp
             src/LTerrainGenerator.cpp
             src/LSceneRenderer.cpp
             src/LShader.cpp
             src/LShaderManager.cpp
             src/LAssetsManager.cpp
             src/LVertexArray.cpp
             src/LVertexBuffer.cpp
             src/LWindow.cpp )

target_link_libraries( gengine 
                       GLEW::GLEW 
                       glfw
                       ${OPENGL_LIBRARIES} )


message( "Configuring gl engine done" )