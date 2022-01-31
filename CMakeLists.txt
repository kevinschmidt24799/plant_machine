cmake_minimum_required(VERSION 3.21)
project(treetest)

set(CMAKE_CXX_STANDARD 17)

add_library(glut_manager
        glut_manager.cpp glut_manager.hpp
        matrix/matrix.cpp matrix/matrix.hpp
        shape.cpp shape.hpp)

find_library(GLUT glut)
find_package(OpenGL REQUIRED)
message("Glut is ${GLUT}")
target_compile_definitions(glut_manager PUBLIC GL_SILENCE_DEPRECATION)
target_link_libraries(glut_manager PUBLIC ${GLUT} ${OPENGL_LIBRARIES})


add_executable(treetest main.cpp
        rect.cpp rect.hpp shape_mst.cpp shape_mst.hpp distance_from_stem.cpp distance_from_stem.hpp)

target_link_libraries(treetest glut_manager)
