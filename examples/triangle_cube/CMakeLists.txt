
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (triangle_cube triangle_cube.cpp)
target_link_libraries (triangle_cube mobile3d ${CORELIBS})

install (TARGETS triangle_cube 
	RUNTIME DESTINATION bin
	)



