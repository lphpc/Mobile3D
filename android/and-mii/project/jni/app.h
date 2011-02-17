
#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include <mobile3d/world.h>
#include <mobile3d/camera.h>
#include <mobile3d/light.h>
#include <mobile3d/model_am.h>

#ifdef __cplusplus
extern "C" {
#endif



// The simple framework expects the application code to define these functions.
void appInit(int width, int height);
void appDeinit();
void appRender(long tick, int width, int height);
void appSetModelTextureOffset (float x, float y, float z);
void appSetModelRotate (float x, float y, float z);
void appSetModelScale (float x, float y, float z);
void appSetModelPosition (float x, float y, float z);
void appSetMiiEyebrow (int id);
void appSetMiiEye (int id);
void appSetMiiNose (int id);
void appSetMiiMouth (int id);


#ifdef __cplusplus
}
#endif


#endif // !APP_H_INCLUDED
