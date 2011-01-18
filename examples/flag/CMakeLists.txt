
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (flag flag.cpp)
target_link_libraries (flag mobile3d ${CORELIBS})

install (TARGETS flag 
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/mobile3d/flag)



