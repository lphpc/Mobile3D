
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (texture texture.cpp)
target_link_libraries (texture mobile3d ${CORELIBS})

install (TARGETS texture 
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/mobile3d/texture)


