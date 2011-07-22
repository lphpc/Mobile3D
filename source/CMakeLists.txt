

if (NOT OPENGLES_FOUND)

	set(HEADER_FILES
		include/m3d.h
		include/world.h
		include/camera.h
		include/model.h
		include/model_am.h
		include/image.h
		include/imageBMP.h
		include/imageRGB.h
		include/imageTGA.h
		include/imagePixelData.h
		include/light.h
		include/log.h
		include/M3DQuad.h
		include/font.h
		include/M3DSkydome.h
		include/M3DSkydomeTexture.h
		include/m3dmath.h
		include/vector3.h
		include/quaternion.h
	)

	set(SOURCE_FILES
		src/world.cpp
		src/camera.cpp
		src/model.cpp
		src/model_am.cpp
		src/image.cpp
		src/imageBMP.cpp
		src/imageRGB.cpp
		src/imageTGA.cpp
		src/imagePixelData.cpp
		src/light.cpp
		src/M3DQuad.cpp
		src/font.cpp
		src/M3DSkydome.cpp
		src/M3DSkydomeTexture.cpp
		src/m3dmath.cpp
		src/vector3.cpp
		src/quaternion.cpp

	)

	include_directories(
  		${CMAKE_CURRENT_SOURCE_DIR}/include
	)



	SET (CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)



else ()

	set(HEADER_FILES
		include/m3d.h
		include/world.h
		include/camera.h
		include/model.h
		include/model_am.h
		include/image.h
		include/imageBMP.h
		include/imageRGB.h
		include/imageTGA.h
		include/imagePixelData.h
		include/light.h
		include/log.h
		include/M3DQuad.h
	)

	set(SOURCE_FILES
		src/world.cpp
		src/camera.cpp
		src/model.cpp
		src/model_am.cpp
		src/image.cpp
		src/imageBMP.cpp
		src/imageRGB.cpp
		src/imageTGA.cpp
		src/imagePixelData.cpp
		src/light.cpp
		src/M3DQuad.cpp
	)

	include_directories(
  		${CMAKE_CURRENT_SOURCE_DIR}/include
  		${OPENGLES_INCLUDE_DIR}
	)



	SET (CORELIBS ${OPENGLES_LIBRARIES} log)
	#SET (CORELIBS ${OPENGLES_LIBRARIES} ${CPP_LIBRARIES})



endif()




ADD_LIBRARY (mobile3d SHARED ${HEADER_FILES} ${SOURCE_FILES} )
ADD_LIBRARY (mobile3d_static STATIC ${SOURCE_FILES} ${HEADER_FILES})
SET_TARGET_PROPERTIES (mobile3d PROPERTIES  OUTPUT_NAME "mobile3d")
SET_TARGET_PROPERTIES (mobile3d_static PROPERTIES OUTPUT_NAME "mobile3d")
SET_TARGET_PROPERTIES (mobile3d PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES (mobile3d_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES (mobile3d PROPERTIES VERSION 1.2 SOVERSION 1)

TARGET_LINK_LIBRARIES(mobile3d ${CORELIBS})
TARGET_LINK_LIBRARIES(mobile3d_static ${CORELIBS})


INSTALL (TARGETS mobile3d mobile3d_static 
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

INSTALL (FILES ${HEADER_FILES} DESTINATION include/mobile3d)

