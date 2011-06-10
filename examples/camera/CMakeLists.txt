
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (camera camera.cpp)
target_link_libraries (camera mobile3d ${CORELIBS})

install (TARGETS camera 
	RUNTIME DESTINATION bin
	)


install (DIRECTORY res/ DESTINATION share/mobile3d/camera)
