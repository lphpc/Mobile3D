
#include <string.h>
#include <math.h>


#include "M3DSkydome.h"



M3D_BEGIN_NAMESPACE

Skydome::Skydome()
{
}
Skydome::~Skydome()
{
	ReleaseDome();
}
void Skydome::GenerateDome(float radius, float dtheta, float dphi, float hTile, float vTile)
{
	int theta, phi;
	// Make sure our vertex array is clear
	/*if (Vertices)
	{
   		delete Vertices;
   		Vertices = NULL;
   		NumVertices = 0;
	}*/

	// Initialize our Vertex array
	NumVertices = (int)((360/dtheta)*(90/dphi)*4);
	Vertices = new VERTEX_SKY[NumVertices];
	memset(Vertices, 0, sizeof(VERTEX_SKY)*NumVertices);
	// Used to calculate the UV coordinates
	float vx, vy, vz, mag;
	// Generate the dome
	int n = 0;
	for (phi=0; phi <= 90 - dphi; phi += (int)dphi)
	{
   		for (theta=0; theta <= 360 - dtheta; theta += (int)dtheta)
   		{
    		// Calculate the vertex at phi, theta
    		Vertices[n].x = radius * sinf(phi*DTOR) * cosf(DTOR*theta);
    		Vertices[n].y = radius * sinf(phi*DTOR) * sinf(DTOR*theta);
    		Vertices[n].z = radius * cosf(phi*DTOR);

    		// Create a vector from the origin to this vertex
    		vx = Vertices[n].x;
			vy = Vertices[n].y;
			vz = Vertices[n].z;

			// Normalize the vector
			mag = (float)sqrt(SQR(vx)+SQR(vy)+SQR(vz));
			vx /= mag;
			vy /= mag;
			vz /= mag;

			// Calculate the spherical texture coordinates
			Vertices[n].u = hTile * (float)(atan2(vx, vz)/(PI*2)) + 0.5f;
			Vertices[n].v = vTile * (float)(asinf(vy) / PI) + 0.5f;  

			n++;

			// Calculate the vertex at phi+dphi, theta
			Vertices[n].x = radius * sinf((phi+dphi)*DTOR) * cosf(theta*DTOR);
			Vertices[n].y = radius * sinf((phi+dphi)*DTOR) * sinf(theta*DTOR);
			Vertices[n].z = radius * cosf((phi+dphi)*DTOR);

			// Calculate the texture coordinates
			vx = Vertices[n].x;
			vy = Vertices[n].y;
			vz = Vertices[n].z;
			mag = (float)sqrt(SQR(vx)+SQR(vy)+SQR(vz));
			vx /= mag;
			vy /= mag;
			vz /= mag;
			Vertices[n].u = hTile * (float)(atan2(vx, vz)/(PI*2)) + 0.5f;
			Vertices[n].v = vTile * (float)(asinf(vy) / PI) + 0.5f;  

			n++;

			// Calculate the vertex at phi, theta+dtheta
			Vertices[n].x = radius * sinf(DTOR*phi) * cosf(DTOR*(theta+dtheta));
			Vertices[n].y = radius * sinf(DTOR*phi) * sinf(DTOR*(theta+dtheta));
			Vertices[n].z = radius * cosf(DTOR*phi);
   
			// Calculate the texture coordinates
			vx = Vertices[n].x;
			vy = Vertices[n].y;
			vz = Vertices[n].z;
			mag = (float)sqrt(SQR(vx)+SQR(vy)+SQR(vz));
			vx /= mag;
			vy /= mag;
			vz /= mag;
			Vertices[n].u = hTile * (float)(atan2(vx, vz)/(PI*2)) + 0.5f;
			Vertices[n].v = vTile * (float)(asinf(vy) / PI) + 0.5f;  

			n++;

    		if (phi > -90 && phi < 90)
    		{
				// Calculate the vertex at phi+dphi, theta+dtheta
				Vertices[n].x = radius * sinf((phi+dphi)*DTOR) * cosf(DTOR*(theta+dtheta));
				Vertices[n].y = radius * sinf((phi+dphi)*DTOR) * sinf(DTOR*(theta+dtheta));
				Vertices[n].z = radius * cosf((phi+dphi)*DTOR);

				// Calculate the texture coordinates
				vx = Vertices[n].x;
				vy = Vertices[n].y;
				vz = Vertices[n].z;
				mag = (float)sqrt(SQR(vx)+SQR(vy)+SQR(vz));
				vx /= mag;
				vy /= mag;
				vz /= mag;
				Vertices[n].u = hTile * (float)(atan2(vx, vz)/(PI*2)) + 0.5f;
				Vertices[n].v = vTile * (float)(asinf(vy) / PI) + 0.5f;  

     			n++;
    		}
   		}
	}


	//得到最低点
	float minZ = Vertices[0].z;
	for(int j=1;j<NumVertices;j++)
	{
		Vertices[j].flag = 0;
		if(Vertices[j].z < minZ)    
			minZ = Vertices[j].z;
	}

	mY = minZ;

	int botNumVertices = 0;
	for(int j=0;j<NumVertices;j++)
	{
		if(Vertices[j].z == minZ)   {
			Vertices[j].flag=1;
			botNumVertices++;
		}
	}

	// Fix the problem at the seam
	for (int i=0; i < NumVertices-3; i++)
	{
		if (Vertices[i].u - Vertices[i+1].u > 0.9f)
			Vertices[i+1].u += 1.0f;
		if (Vertices[i+1].u - Vertices[i].u > 0.9f)
			Vertices[i].u += 1.0f;
		if (Vertices[i].u - Vertices[i+2].u > 0.9f)
			Vertices[i+2].u += 1.0f;
		if (Vertices[i+2].u - Vertices[i].u > 0.9f)
			Vertices[i].u += 1.0f;
		if (Vertices[i+1].u - Vertices[i+2].u > 0.9f)
			Vertices[i+2].u += 1.0f;
		if (Vertices[i+2].u - Vertices[i+1].u > 0.9f)
			Vertices[i+1].u += 1.0f;
		if (Vertices[i].v - Vertices[i+1].v > 0.8f)
			Vertices[i+1].v += 1.0f;
		if (Vertices[i+1].v - Vertices[i].v > 0.8f)
			Vertices[i].v += 1.0f;
		if (Vertices[i].v - Vertices[i+2].v > 0.8f)
			Vertices[i+2].v += 1.0f;
		if (Vertices[i+2].v - Vertices[i].v > 0.8f)
			Vertices[i].v += 1.0f;
		if (Vertices[i+1].v - Vertices[i+2].v > 0.8f)
			Vertices[i+2].v += 1.0f;
		if (Vertices[i+2].v - Vertices[i+1].v > 0.8f)
			Vertices[i+1].v += 1.0f;
	}


        setMeshCount(2);

        float *vertices0 = (float *) malloc(NumVertices * 3 * sizeof(float));
        GLubyte *colors0 = (GLubyte *) malloc(NumVertices * 4 * sizeof(GLubyte));
        float *uvs0 = (float *) malloc(NumVertices * 2 * sizeof(float));

        setTriangleNums(NumVertices/3);

		int ver_id = 0;
		int uv_id = 0;
		int color_id = 0;
		for (int i=0; i < NumVertices; i++)
		{

			vertices0[ver_id++] = Vertices[i].x;
			vertices0[ver_id++] = Vertices[i].y;
			vertices0[ver_id++] = Vertices[i].z;

			if (Vertices[i].flag == 1) {

				colors0[color_id++] = 242; 
				colors0[color_id++] = 242;
				colors0[color_id++] = 255;
				colors0[color_id++] = 0;

			}
			else {
				colors0[color_id++] = 51; 
				colors0[color_id++] = 128;
				colors0[color_id++] = 255;
				colors0[color_id++] = 0;
			}

			uvs0 [uv_id++] =  Vertices[i].u;
			uvs0 [uv_id++] =  Vertices[i].v;

		}


        setVertices(vertices0, NumVertices * 3 * sizeof(float));
        setColors(colors0, NumVertices * 4 * sizeof(GLubyte));
        setUvs(uvs0, NumVertices * 6 * sizeof(float));

		setRenderPrimitivesMode (GL_TRIANGLE_STRIP);

        FREEANDNULL(vertices0);
        FREEANDNULL(colors0);
        FREEANDNULL(uvs0);


        float *vertices1 = (float *) malloc(botNumVertices * 3 * sizeof(float));
        GLubyte *colors1 = (GLubyte *) malloc(botNumVertices * 4 * sizeof(float));

        setTriangleNums(botNumVertices/3, 1);

		ver_id = 0;
		color_id = 0;
		for (int i=0; i < NumVertices; i++)
		{


			if (Vertices[i].flag == 1) {

				vertices1[ver_id++] = Vertices[i].x;
				vertices1[ver_id++] = Vertices[i].y;
				vertices1[ver_id++] = Vertices[i].z;

				colors1[color_id++] = 230; 
				colors1[color_id++] = 230;
				colors1[color_id++] = 255;
				colors1[color_id++] = 0;

			}

		}


        setVertices(vertices1, botNumVertices * 3 * sizeof(float), 1);
        setColors(colors1, botNumVertices * 4 * sizeof(GLubyte), 1);

		setRenderPrimitivesMode (GL_TRIANGLE_FAN, 1);

        FREEANDNULL(vertices1);
        FREEANDNULL(colors1);

        //for map3d
		setPosition (400.0f, 200.0f, -50.0f);


		//for examples/skydome
//		setPosition (0.0f, -100.0f, 0.0f);
//		setRotate (270, 1.0f, 0.0f);


		

	
}
/*
int Skydome::RenderSkyDome(float x,float y,float z)
{
	return;

	glPushMatrix();
	//glTranslatef(0.0f, -100.0f, 0.0f);
	glTranslatef(x, y-100, z);
	//glRotatef(timeGetTime()/2000.0f,0.0f, 1.0f, 0.0f);
	glRotatef(270, 1.0f, 0.0f, 0.0f);

	glColor4f(1,1,1,1);

	glBegin(GL_TRIANGLE_STRIP);
	//glBegin(GL_LINE_STRIP);
	for (int i=0; i < NumVertices; i++)
	{
		if(Vertices[i].flag==1) //最后一圈顶点
			//glColor3f(0.9f,0.9f,1.0f);
			glColor3f(0.95f,0.95f,1.0f);
		else
			//glColor3f(0.5f, 0.7f, 0.8f);
			glColor3f(0.2f, 0.5f, 1.0f);  

		glTexCoord2f(Vertices[i].u, Vertices[i].v);
		glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
	}
	glEnd();

	//闭合底部
	glColor3f(0.9f,0.9f,1.0f);
	glBegin(GL_POLYGON);
	for(int i=0;i<NumVertices;i++)
	{
		if(Vertices[i].flag == 1)
		{
			glTexCoord2f(Vertices[i].u, Vertices[i].v);
			glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
		}
	}
	glEnd();

	glPopMatrix();
	return 1;
}
*/

void Skydome::ReleaseDome()
{
	if (Vertices)
	{
		delete Vertices;
		Vertices = NULL;
	}
}


M3D_END_NAMESPACE
