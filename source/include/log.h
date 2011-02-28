
#ifndef _M3D_LOG_H
#define _M3D_LOG_H

#include "m3d.h"

#ifdef __cplusplus
extern "C" {
#endif


#if defined(OPENGL)  /* PC */
#   define _M3D_PRINTF(fmt...) fprintf (stderr, fmt)
#else /* android */

#define _M3D_PRINTF(...) __android_log_print(ANDROID_LOG_INFO, "Mobile3D", __VA_ARGS__)

#endif


#define GL_CHECK_ERROR \
    { \
        int e = glGetError(); \
        if (e != 0) \
        { \
            _M3D_PRINTF ("OpenGL error 0x%04X at line %i in %s\n", e, __LINE__, __FILE__); \
        } \
    }





#ifdef __cplusplus
}
#endif


#endif
