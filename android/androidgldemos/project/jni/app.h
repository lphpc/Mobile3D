
#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include <mobile3d/world.h>
#include <mobile3d/camera.h>
#include <mobile3d/model.h>
#include <mobile3d/imageBMP.h>
#include <mobile3d/imageRGB.h>
#include <mobile3d/imageTGA.h>
#include <mobile3d/model_am.h>

#ifdef __cplusplus
extern "C" {
#endif



// The simple framework expects the application code to define these functions.
void appInitTriangle(int width, int height);
void appDeinitTriangle();
void appRenderTriangle(long tick, int width, int height);
void appSetModelTextureOffsetTriangle (float x, float y, float z);
void appSetModelRotateTriangle (float x, float y, float z);
void appSetModelScaleTriangle (float x, float y, float z);
void appSetModelPositionTriangle (float x, float y, float z);


void appInitTexture(int width, int height);
void appDeinitTexture();
void appRenderTexture(long tick, int width, int height);
void appSetModelTextureOffsetTexture (float x, float y, float z);
void appSetModelRotateTexture (float x, float y, float z);
void appSetModelScaleTexture (float x, float y, float z);
void appSetModelPositionTexture (float x, float y, float z);


void appInitBlending(int width, int height);
void appDeinitBlending();
void appRenderBlending(long tick, int width, int height);
void appSetModelTextureOffsetBlending (float x, float y, float z);
void appSetModelRotateBlending (float x, float y, float z);
void appSetModelScaleBlending (float x, float y, float z);
void appSetModelPositionBlending (float x, float y, float z);

void appInitCaustics(int width, int height);
void appDeinitCaustics();
void appRenderCaustics(long tick, int width, int height);
void appSetModelTextureOffsetCaustics (float x, float y, float z);
void appSetModelRotateCaustics (float x, float y, float z);
void appSetModelScaleCaustics (float x, float y, float z);
void appSetModelPositionCaustics (float x, float y, float z);

void appInitFlag(int width, int height);
void appDeinitFlag();
void appRenderFlag(long tick, int width, int height);
void appSetModelTextureOffsetFlag (float x, float y, float z);
void appSetModelRotateFlag (float x, float y, float z);
void appSetModelScaleFlag (float x, float y, float z);
void appSetModelPositionFlag (float x, float y, float z);


void appInitAndMii(int width, int height);
void appDeinitAndMii();
void appRenderAndMii(long tick, int width, int height);
void appSetModelTextureOffsetAndMii (float x, float y, float z);
void appSetModelRotateAndMii (float x, float y, float z);
void appSetModelScaleAndMii (float x, float y, float z);
void appSetModelPositionAndMii (float x, float y, float z);
void appSetMiiEyebrow (int id);
void appSetMiiEye (int id);
void appSetMiiNose (int id);
void appSetMiiMouth (int id);

void appInitWater(int width, int height);
void appDeinitWater();
void appRenderWater(long tick, int width, int height);
void appSetModelTextureOffsetWater (float x, float y, float z);
void appSetModelRotateWater (float x, float y, float z);
void appSetModelScaleWater (float x, float y, float z);
void appSetModelPositionWater (float x, float y, float z);
void appSetWaterWave (int x, int y, int width, int height);
void appClearWaterWave ();




#ifdef __cplusplus
}
#endif


#endif // !APP_H_INCLUDED
