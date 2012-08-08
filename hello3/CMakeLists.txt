
cmake_minimum_required(VERSION 2.6)
project(HELLO3)

find_package(GLUT)
find_package(OpenGL)

set(CMAKE_C_FLAGS "-g -Wall")
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable(hello3 main.c)
target_link_libraries(hello3 ${CORELIBS})
