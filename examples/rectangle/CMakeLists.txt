
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

add_executable (rectangle rectangle.cpp)
target_link_libraries (rectangle mobile3d ${CORELIBS})


install (TARGETS rectangle 
	RUNTIME DESTINATION bin
	)



