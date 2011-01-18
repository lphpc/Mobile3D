
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (sea sea.cpp)
target_link_libraries (sea mobile3d ${CORELIBS})


install (TARGETS sea 
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/mobile3d/sea)


