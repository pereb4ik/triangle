cmake_minimum_required(VERSION 3.17)
project(triangle)

set(CMAKE_CXX_STANDARD 14)

#find_package(X11 REQUIRED)
#link_libraries(${X11_LIBRARIES})
#include_directories(${X11_INCLUDE_DIR})

#find_package(OpenGL REQUIRED OpenGL GLX)
#include_directories( ${OPENGL_INCLUDE_DIRS} )
#link_libraries(${OPENGL_LIBRARIES})

include_directories(/opt/X11/include/)
link_directories(/opt/X11/lib)


add_executable(triangle main.cpp)
target_link_libraries(triangle GL GLU X11)