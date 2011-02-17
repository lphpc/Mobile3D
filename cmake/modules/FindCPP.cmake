# - Try to find OpenGLES
# Once done this will define
#  
#  CPP_FOUND        - system has OpenGLES
#  CPP_INCLUDE_DIR  - the GL include directory
#  CPP_LIBRARIES    - Link these to use OpenGLES

MESSAGE(STATUS "Using bundled FindCPP.cmake...")



FIND_PATH(
	CPP_INCLUDE_DIR stdio.h 
   	/home/liuuupen/android/android-ndk-r5/platforms/android-9/arch-arm/usr/include/ 
)

FIND_LIBRARY(
	CPP_LIBRARIES NAMES  stdc++
   	PATHS /home/liuuupen/android/android-ndk-r5/platforms/android-9/arch-arm/usr/lib/ 
)

MARK_AS_ADVANCED(
  CPP_INCLUDE_DIR
  CPP_LIBRARIES
)


