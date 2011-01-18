
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (3dclock clock.cpp)
target_link_libraries (3dclock mobile3d ${CORELIBS})

install (TARGETS 3dclock
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/mobile3d/3dclock)



