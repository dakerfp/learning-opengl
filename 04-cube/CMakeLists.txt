
cmake_minimum_required(VERSION 2.6)
project(CUBE)

find_package(GLUT)
find_package(OpenGL)

set(CMAKE_C_FLAGS "-g -Wall")
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable(cube main.c)
target_link_libraries(cube ${CORELIBS})
