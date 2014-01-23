cmake_minimum_required(VERSION 2.8)

project(pgm3d-viewer)
add_executable(pgm3d-viewer main.cpp GraphicsScene.cpp GraphicsPGM3DItem.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(pgm3d-viewer ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
