
cmake_minimum_required(VERSION 2.8)
PROJECT (MOBILE3DLIB)

if(NOT CMAKE_BUILD_TYPE)
	SET (CMAKE_BUILD_TYPE "RelWithDebInfo")
ENDIF()


#SET( ANDROID "YES" )

add_definitions(-DMAC)
add_definitions(-DOPENGL)


if (NOT ANDROID)

find_package(GLUT)
find_package(OpenGL)


#ADD_SUBDIRECTORY(source)
ADD_SUBDIRECTORY(examples)


else ()

	SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules) 
	find_package(OpenGLES)
	find_package(Mobile3D)

	IF (OPENGLES_INCLUDE_DIR AND OPENGLES_LIBRARIES)
		MESSAGE(STATUS "Found OpenGLES libraries")
		MESSAGE (STATUS "gles dir:" ${OPENGLES_INCLUDE_DIR})
		MESSAGE (STATUS "gles lib:" ${OPENGLES_LIBRARIES})

	ELSE (OPENGLES_INCLUDE_DIR AND OPENGLES_LIBRARIES)
		MESSAGE(STATUS "Fail to found OpenGLES libraries")
	ENDIF (OPENGLES_INCLUDE_DIR AND OPENGLES_LIBRARIES)


	ADD_SUBDIRECTORY(source)

endif()










