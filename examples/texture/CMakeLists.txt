
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (texture texture.cpp)
target_link_libraries (texture mobile3d ${CORELIBS})


