
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (model_am model_am.cpp)
target_link_libraries (model_am mobile3d ${CORELIBS})


install (TARGETS model_am
	RUNTIME DESTINATION bin
	)

install (DIRECTORY res/ DESTINATION share/mobile3d/model_am)

