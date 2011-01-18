
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (caustics caustics.cpp)
target_link_libraries (caustics mobile3d ${CORELIBS})

install (TARGETS caustics 
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/mobile3d/caustics)




