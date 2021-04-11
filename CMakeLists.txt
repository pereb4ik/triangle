cmake_minimum_required(VERSION 3.00)
project(triangle)

set(CMAKE_CXX_STANDARD 14)

if (LINUX OR (UNIX AND NOT APPLE))
    find_package(X11 REQUIRED)
    link_libraries(${X11_LIBRARIES})
    include_directories(${X11_INCLUDE_DIR})

    find_package(OpenGL REQUIRED OpenGL GLX)
    include_directories(${OPENGL_INCLUDE_DIRS})
    link_libraries(${OPENGL_LIBRARIES})
endif ()

if (APPLE)
    include_directories(/opt/X11/include/)
    link_directories(/opt/X11/lib)
    link_libraries(GL X11)
endif ()

add_executable(triangle main.cpp)
