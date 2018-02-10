
cmake_minimum_required( VERSION 3.5.0 )
project( finalproject C CXX )

set( CMAKE_BUILD_TYPE Debug )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_FLAGS_DEBUG "-g -Wno-unused-parameter -Wno-delete-incomplete" )
set( CMAKE_CXX_FLAGS_RELEASE "-O3 -Wno-unused-parameter" )

find_package( Bullet REQUIRED )

message( "bullet libraries: ${BULLET_LIBRARIES}" )
message( "bullet includes: ${BULLET_INCLUDE_DIRS}" )

if( WIN32 )

  message( "making finalproject for windows" )
  
  # link_directories( ext/glew/lib/Release/x64 
  #                   ext/glfw/lib-vc2015 )

elseif( UNIX AND NOT APPLE )

  message( "CONFIGURING finalproject FOR LINUX" )

  find_package( OpenGL REQUIRED )
  find_package( GLEW REQUIRED )

elseif( APPLE )

  message( "CONFIGURING finalproject FOR APPLE" )

  find_package( OpenGL REQUIRED )
  find_package( GLEW REQUIRED )

endif()

include_directories( gengine/include 
                     # ext/glew/include 
                     ext/glfw/include 
                     ext/glm/
                     ext/stb )

add_subdirectory( ext/glfw )
add_subdirectory( ext/glm )
# add_subdirectory( ext/glew )
add_subdirectory( gengine )

add_subdirectory( tests )





# add_library( fengine
#              LCommon.cpp
#              LComponent.cpp
#              LEntity.cpp
#              LFixedCamera3d.cpp
#              LFpsCamera.cpp
#              LInputHandler.cpp
#              LICamera.cpp
#              LIndexBuffer.cpp
#              LTexture.cpp
#              LCubeTexture.cpp
#              LSkybox.cpp
#              LMeshBuilder.cpp
#              LMeshComponent.cpp
#              LHeightmapGenerator.cpp
#              LTerrainPatch.cpp
#              LMesh.cpp
#              LScene.cpp
#              LTerrainGenerator.cpp
#              LSceneRenderer.cpp
#              LShader.cpp
#              LShaderManager.cpp
#              LAssetsManager.cpp
#              LVertexArray.cpp
#              LVertexBuffer.cpp
#              LWindow.cpp )

# target_link_libraries( fengine 
#                        glfw
#                        ${OPENGL_LIBRARIES} 
#                        GLEW::GLEW 
#                        ${GLUT_LIBRARY} )

# if( WIN32 )

#     message( "Building finalproject - windows" )
#     message( "Sorry, haven't configured it yet. Use either linux or macos" )

# elseif( UNIX AND NOT APPLE )

#     message( "Building finalproject - linux" )
#     add_executable( finalproject.out
#                     main.cpp )

#     if ( WINDOWING_SYSTEM STREQUAL "GLFW" )

#         message( "GLFW!!!!" )

#         target_link_libraries( finalproject.out )

#     elseif( WINDOWING_SYSTEM STREQUAL "GLUT" )

#         message( "GLUT!!!!" )

#         target_link_libraries( finalproject.out
#                                ${OPENGL_LIBRARIES} 
#                                GLEW::GLEW 
#                                ${GLUT_LIBRARY} 
#                                BulletDynamics
#                                BulletCollision
#                                LinearMath )
#     else()

#         message( "WINDOWING_SYSTEM NOT SET CORRECTLY" )

#     endif()

# elseif( APPLE )

#     message( "Building finalproject - macOS" )
#     add_executable( finalproject.out
#                     main.cpp 
#                     LCommon.cpp
#                     LComponent.cpp
#                     LEntity.cpp
#                     LFixedCamera3d.cpp
#                     LFpsCamera.cpp
#                     LInputHandler.cpp
#                     LICamera.cpp
#                     LIndexBuffer.cpp
#                     LTexture.cpp
#                     LMeshBuilder.cpp
#                     LMeshComponent.cpp
#                     LHeightmapGenerator.cpp
#                     LTerrainPatch.cpp
#                     LMesh.cpp
#                     LScene.cpp
#                     LTerrainGenerator.cpp
#                     LSceneRenderer.cpp
#                     LShader.cpp
#                     LShaderManager.cpp
#                     LVertexArray.cpp
#                     LVertexBuffer.cpp
#                     LWindow.cpp )

#     if ( ${WINDOWING_SYSTEM} EQUAL "GLFW" )

#         target_link_libraries( finalproject.out glfw
#                                ${OPENGL_LIBRARIES} 
#                                GLEW::GLEW 
#                                ${GLUT_LIBRARY} 
#                                BulletDynamics
#                                BulletCollision
#                                LinearMath )

#     elseif( ${WINDOWING_SYSTEM} EQUAL "GLUT" )

#         target_link_libraries( finalproject.out
#                                ${OPENGL_LIBRARIES} 
#                                GLEW::GLEW 
#                                ${GLUT_LIBRARY} 
#                                BulletDynamics
#                                BulletCollision
#                                LinearMath )
#     else()

#         message( "WINDOWING_SYSTEM NOT SET CORRECTLY" )

#     endif()
# endif()


# add_executable( testBullet
#                 testBullet.cpp )

# target_link_libraries( testBullet 
#                        LinearMath
#                        BulletDynamics
#                        BulletCollision )
