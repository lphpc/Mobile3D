
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (mii mii.cpp)
target_link_libraries (mii mobile3d ${CORELIBS})


install (TARGETS mii
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/mobile3d/mii)



