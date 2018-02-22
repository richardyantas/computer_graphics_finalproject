
include_directories( "${CMAKE_SOURCE_DIR}/ext/ui_dearImgui/imgui" 
                     "${CMAKE_SOURCE_DIR}/ext/ui_dearImgui/cat1UI" 
                     "${CMAKE_SOURCE_DIR}/ext/glfw/include" 
                     "${CMAKE_SOURCE_DIR}/ext/glad/include"
                     "${CMAKE_SOURCE_DIR}/ext/ui_dearImgui/imgui/examples/opengl3_example" )

if ( WIN32 )

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

endif()

add_library( cat1UI
             imgui/imgui.cpp
             imgui/imgui_draw.cpp
             imgui/imgui_demo.cpp
             imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp
             cat1UI/LUIWidgets.cpp
             cat1UI/LUIWindow.cpp
             cat1UI/LUIHandler.cpp )

target_link_libraries( cat1UI 
                       glfw glad 
                       ${OPENGL_LIBRARIES} )