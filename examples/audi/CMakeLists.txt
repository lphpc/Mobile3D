
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (audi audi.cpp)
target_link_libraries (audi mobile3d ${CORELIBS})


install (TARGETS audi
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/mobile3d/audi)

