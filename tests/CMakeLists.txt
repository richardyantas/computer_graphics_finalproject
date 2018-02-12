
message( "Configuring tests" )

include_directories( ${BULLET_INCLUDE_DIRS} ../gengine/include ../tysoc/include )
link_directories( ../lib /usr/local/lib )

add_executable( testBullet
                testBullet.cpp )

target_link_libraries( testBullet
                       gengine
                       BulletCollision
                       BulletDynamics
                       LinearMath )

add_executable( testGL
                testGL.cpp )

target_link_libraries( testGL
                       gengine )

add_executable( testBulletGL
                testBulletGL.cpp )

target_link_libraries( testBulletGL
                       gengine
                       BulletCollision
                       BulletDynamics
                       LinearMath )

add_executable( testTysoc
                testTysoc.cpp )

target_link_libraries( testTysoc
                       tysoc )