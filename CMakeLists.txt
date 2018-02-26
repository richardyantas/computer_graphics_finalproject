
cmake_minimum_required( VERSION 3.5.0 )
project( finalproject C CXX )

set( CMAKE_BUILD_TYPE Debug )

set( CMAKE_CXX_STANDARD 11 )

find_package( OpenGL REQUIRED )

message( "CONFIGURING EXTERNAL DEPENDENCIES" )
# add_subdirectory( ext/jsoncpp )
add_subdirectory( ext/glfw )
add_subdirectory( ext/glad )
add_subdirectory( ext/glm )
add_subdirectory( ext/ui_dearImgui )

set( TYSOC_INCLUDE_DIRECTORIES
     "${CMAKE_SOURCE_DIR}/gengine/include"
     "${CMAKE_SOURCE_DIR}/tysoc/include"
     # "${CMAKE_SOURCE_DIR}/ext/jsoncpp/include"
     "${CMAKE_SOURCE_DIR}/ext/glfw/include"
     "${CMAKE_BINARY_DIR}/ext/glad/include" # glad generates .h files in build dir :o
     "${CMAKE_SOURCE_DIR}/ext/glm/"
     "${CMAKE_SOURCE_DIR}/ext/stb/"
     "${CMAKE_SOURCE_DIR}/ext/ui_dearImgui/imgui"
     "${CMAKE_SOURCE_DIR}/ext/ui_dearImgui/imgui/examples/opengl3_example"
     "${CMAKE_SOURCE_DIR}/ext/ui_dearImgui/cat1UI" )

#set( TYSOC_LIBRARY_DIRECTORIES "" )

option( LIBRARIES_BULLET_USE_PREBUILT "Use prebuilt bullet libraries for the build" OFF )

add_definitions( -DTYSOC_RESOURCES_PATH="${CMAKE_SOURCE_DIR}/res/" )

message( "tysoc resources path: ${CMAKE_SOURCE_DIR}/res/" )

if( WIN32 )

    message( "CONFIGURING finalproject FOR WINDOWS" )

    set( CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /GR /EHsc" )
    set( CMAKE_CXX_FLAGS_DEBUG "/MTd /Zi /Ob0 /Od /RTC1 -D_DEBUG" )
    set( CMAKE_CXX_FLAGS_RELEASE "/MT /O2 /Ob2 /DNDEBUG" )
    set( CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O1 /Ob1 /DNDEBUG" )
    set( CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MT /Zi /O2 /Ob1 /DNDEBUG" )
    set( CMAKE_C_FLAGS "/DWIN32 /D_WINDOWS /W3" )
    set( CMAKE_C_FLAGS_DEBUG "/MTd /Zi /Ob0 /Od /RTC1" )
    set( CMAKE_C_FLAGS_RELEASE "/MT /O2 /Ob2 /DNDEBUG" )
    set( CMAKE_C_FLAGS_MINSIZEREL "/MT /O1 /Ob1 /DNDEBUG" )
    set( CMAKE_C_FLAGS_RELWITHDEBINFO "/MT /Zi /O2 /Ob1 /DNDEBUG" )

    if ( LIBRARIES_BULLET_USE_PREBUILT )
        # set path to prebuilt libraries
        set( LIBRARIES_BULLET_PREBUILT_LIBS "${CMAKE_SOURCE_DIR}/ext/BULLET_PHYSICS" CACHE STRING "Path to bullet prebuilt libraries" )

        set( BULLET_INCLUDE_DIRS "${LIBRARIES_BULLET_PREBUILT_LIBS}/include" )
        set( BULLET_LIBRARY_DIRS "${LIBRARIES_BULLET_PREBUILT_LIBS}/lib" )

    else()
        # using from submodule
        message( "CONFIGURING Bullet3 from submodule" )

        add_subdirectory( ext/bullet3 )

        set( BULLET_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/ext/bullet3/src/" )
        set( BULLET_LIBRARY_DIRS "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}/" )

    endif()

elseif( UNIX AND NOT APPLE )

    message( "CONFIGURING finalproject FOR LINUX" )

    find_package( Bullet )

    if ( BULLET_FOUND )

        message( "FOUND BULLET IN FILESYSTEM" )
        message( "bullet libraries: ${BULLET_LIBRARIES}" )
        message( "bullet includes: ${BULLET_INCLUDE_DIRS}" )

    else()
        message( "Bullet3 library not found, give specific path to library" )
        # Try to find it somewhere else
        set( BULLET_DIR "/home/" ) # set the BULLET_DIR variable to find the bullet directory


    endif()

elseif( APPLE )

    message( "CONFIGURING finalproject FOR APPLE" )

endif()

## message( "bullet dirs: ${BULLET_INCLUDE_DIRS}" )
set( TYSOC_INCLUDE_DIRECTORIES 
     "${TYSOC_INCLUDE_DIRECTORIES}" 
     "${BULLET_INCLUDE_DIRS}" )
set( TYSOC_LIBRARY_DIRECTORIES "${BULLET_LIBRARY_DIRS}" )
#message( "tysoc include dirs: ${TYSOC_INCLUDE_DIRECTORIES}" )
#message( "tysoc library dirs: ${TYSOC_LIBRARY_DIRECTORIES}" )

include_directories( ${TYSOC_INCLUDE_DIRECTORIES} )
#link_directories( ${TYSOC_LIBRARY_DIRECTORIES} )

message( "CONFIGURING ENGINE LIBRARIES" )
add_subdirectory( gengine )
add_subdirectory( tysoc )

message( "CONFIGURING TESTS" )
add_subdirectory( tests )

FOREACH(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO )
    message( "flag_var: ${flag_var} ${${flag_var}}" )
ENDFOREACH(flag_var)