
#ifndef _M3D_LOG_H
#define _M3D_LOG_H


#ifdef __cplusplus
extern "C" {
#endif


#if defined(OPENGL)
#   define _M3D_PRINTF(fmt...) fprintf (stderr, fmt)
#else /* PC */
static inline void _M3D_PRINTF(const char* fmt, ...)
{
	__android_log_print(ANDROID_LOG_INFO, "Mobile3D",  fmt);
}
#endif /* android */





#ifdef __cplusplus
}
#endif


#endif
