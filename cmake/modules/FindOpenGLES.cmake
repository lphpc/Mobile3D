# - Try to find OpenGLES
# Once done this will define
#  
#  OPENGLES_FOUND        - system has OpenGLES
#  OPENGLES_INCLUDE_DIR  - the GL include directory
#  OPENGLES_LIBRARIES    - Link these to use OpenGLES

MESSAGE(STATUS "Using bundled FindOpenGLES.cmake...")

FIND_PATH(
	OPENGLES_INCLUDE_DIR GLES/gl.h 
   	/home/liuuupen/android/android-ndk-r5/build/platforms/android-8/arch-arm/usr/include/ 
)

FIND_LIBRARY(
	OPENGLES_LIBRARIES NAMES  GLESv1_CM
   	PATHS /home/liuuupen/android/android-ndk-r5/build/platforms/android-8/arch-arm/usr/lib/ 
)

SET( OPENGLES_FOUND "NO" )
IF(OPENGLES_LIBRARIES)

    SET( OPENGLES_FOUND "YES" )


ENDIF(OPENGLES_LIBRARIES)



MARK_AS_ADVANCED(
  OPENGLES_INCLUDE_DIR
  OPENGLES_LIBRARIES
)


