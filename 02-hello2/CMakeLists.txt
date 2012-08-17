
cmake_minimum_required(VERSION 2.6)
project(HELLO2)

find_package(GLUT)
find_package(OpenGL)

set(CMAKE_CXX_FLAGS "-g -Wall")
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable(hello2 main.c)
target_link_libraries(hello2 ${CORELIBS})
