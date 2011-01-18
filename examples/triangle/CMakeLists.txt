
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (triangle triangle.cpp)
target_link_libraries (triangle mobile3d ${CORELIBS})

install (TARGETS triangle 
	RUNTIME DESTINATION bin
	)



