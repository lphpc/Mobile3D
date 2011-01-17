
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (mii meshes.cpp mii.cpp)
target_link_libraries (mii mobile3d ${CORELIBS})


