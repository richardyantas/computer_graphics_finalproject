
message( "Configuring tests" )

include_directories( ${TYSOC_INCLUDE_DIRECTORIES} )
link_directories( ${TYSOC_LIBRARY_DIRECTORIES} )


add_executable( testGLfeatures
                testGLfeatures.cpp )

target_link_libraries( testGLfeatures
					   tysoc )

add_executable( testPrimitives
                testPrimitives.cpp )

target_link_libraries( testPrimitives
					   tysoc )

add_executable( testScenario
                testScenario.cpp )

if ( BULLET_FOUND )

target_link_libraries( testScenario
					   ${BULLET_LIBRARIES}
                       tysoc )

else()

target_link_libraries( testScenario
                       tysoc )

endif()