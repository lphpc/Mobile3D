
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





#ifdef __cplusplus
}
#endif


#endif
