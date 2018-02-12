
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
                     ext/glfw/include 
                     ext/glm/
                     ext/stb )

add_subdirectory( ext/glfw )
add_subdirectory( ext/glm )
add_subdirectory( gengine )
add_subdirectory( tysoc )

add_subdirectory( tests )




