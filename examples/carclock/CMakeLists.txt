
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (carclock carclock.cpp)
target_link_libraries (carclock mobile3d ${CORELIBS})

install (TARGETS carclock
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/mobile3d/carclock)



