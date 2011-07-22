
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (skydome_app skydome.h skydome.cpp skydome_app.cpp)
target_link_libraries (skydome_app mobile3d ${CORELIBS})

install (TARGETS skydome_app 
	RUNTIME DESTINATION bin
	)


#install (DIRECTORY res/ DESTINATION share/mobile3d/skydome)

