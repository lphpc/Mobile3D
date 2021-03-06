
#ifndef _M3D_H_
#define _M3D_H_

#ifdef __cplusplus
extern "C" {
#endif



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef OPENGL

#ifdef MAC
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif  //end of MAC

#else 
#include <GLES/gl.h>
#include <android/log.h>
#endif  //end of OPENGL

#define M3D_BEGIN_NAMESPACE namespace M3D {
#define M3D_END_NAMESPACE }

typedef double mdouble;
typedef float mfloat;

typedef GLfloat Real;


enum M3D_BitmapConfig{
	M3D_RGB, M3D_RGBA
};


typedef struct _Color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Color;


typedef struct _Texture {
    GLsizei width;
    GLsizei height;
    GLuint textureId;
	GLuint  type;
} Texture;



#ifndef M_PI
#define M_PI 3.1415926535897932f
#endif


#define DTOR (M_PI / 180.0f)
#define SQR(x) (x * x)

#define FREEANDNULL(pointer) \
    if (pointer != NULL) { \
        free(pointer); \
        pointer = NULL; \
    }



#ifdef __cplusplus
}
#endif

#endif //_M3D_H

