
message( "Configuring tests" )

include_directories( ${TYSOC_INCLUDE_DIRECTORIES} )
#link_directories( ${TYSOC_LIBRARY_DIRECTORIES} )

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

add_executable( testShadowMapping
                testShadowMapping.cpp )

target_link_libraries( testShadowMapping
                       gengine cat1UI )

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

add_executable( testPrimitives
                testPrimitives.cpp )

target_link_libraries( testPrimitives
                       tysoc )

add_executable( testScenario
                testScenario.cpp )

target_link_libraries( testScenario
                       tysoc )