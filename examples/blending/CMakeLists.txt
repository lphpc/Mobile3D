
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (blending blending.cpp)
target_link_libraries (blending mobile3d ${CORELIBS})

install (TARGETS blending 
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/mobile3d/blending)


