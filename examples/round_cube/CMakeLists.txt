
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (round_cube round_cube.cpp)
target_link_libraries (round_cube mobile3d ${CORELIBS})


install (TARGETS round_cube
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/mobile3d/round_cube)

