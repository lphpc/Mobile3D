
#ifndef _M3D_SKYDOME_H_
#define _M3D_SKYDOME_H_


#include "model.h"


M3D_BEGIN_NAMESPACE

#ifndef PI
#define PI 3.1415926535897f
#endif
#ifndef DTOR
#define DTOR (PI/180.0f)
#endif
#ifndef SQR
#define SQR(x) (x*x)
#endif


typedef struct {
	float x,y,z;
	unsigned int color;
	float u, v;
	int   flag;
} VERTEX_SKY;



class Skydome: public Model 
{
public:
	Skydome();
	~Skydome();
	void GenerateDome(float radius, float dtheta, float dphi, float hTile, float vTile);

protected:
	void ReleaseDome();

private:
	VERTEX_SKY *Vertices;
	int NumVertices;
	float mY;
};


M3D_END_NAMESPACE

#endif


