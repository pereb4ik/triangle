cmake_minimum_required(VERSION 3.17)
project(triangle)

set(CMAKE_CXX_STANDARD 14)

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
link_libraries(${X11_LIBRARIES})

find_package(OpenGL REQUIRED OpenGL GLX)
include_directories(${OPENGL_INCLUDE_DIRS})
link_libraries(${OPENGL_LIBRARIES})

#include_directories(/opt/X11/include/) # uncomment for compile on macOS
#link_directories(/opt/X11/lib) # uncomment for compile on macOS
#link_libraries(GL X11) # uncomment for compile on macOS

add_executable(triangle main.cpp)
