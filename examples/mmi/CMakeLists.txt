
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (mmi mmi.cpp)
target_link_libraries (mmi mobile3d ${CORELIBS})

install (TARGETS mmi 
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/mobile3d/mmi)


