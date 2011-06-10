
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (map map.cpp)
target_link_libraries (map mobile3d ${CORELIBS})

install (TARGETS map 
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/mobile3d/map)


