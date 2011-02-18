
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (quad quad.cpp)
target_link_libraries (quad mobile3d ${CORELIBS})


install (TARGETS quad
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/mobile3d/quad)

