
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (skydome skydome.cpp)
target_link_libraries (skydome mobile3d ${CORELIBS})

install (TARGETS skydome 
	RUNTIME DESTINATION bin
	)


install (DIRECTORY res/ DESTINATION share/mobile3d/skydome)

