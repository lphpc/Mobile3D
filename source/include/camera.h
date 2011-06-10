
#ifndef _CAMERA_H
#define _CAMERA_H

#include "m3d.h"
#include "quaternion.h"


M3D_BEGIN_NAMESPACE

	class Camera {

	private:
        GLfloat m_eyex;
        GLfloat m_eyey;
        GLfloat m_eyez;
        GLfloat m_centerx;
        GLfloat m_centery;
        GLfloat m_centerz;
        GLfloat m_upx;
        GLfloat m_upy;
        GLfloat m_upz;
        //private functions
        void crossf(float v0[3], float v1[3], float r[3]);
        void normalizef(float v[3]);
        void identf(GLfloat m[]);

	public:

        Camera();
        ~Camera();

        void setEye(GLfloat eyex, GLfloat eyey, GLfloat eyez);
        void setCenter(GLfloat centerx, GLfloat centery, GLfloat centerz);
        void setUp(GLfloat upx, GLfloat upy, GLfloat upz);
        void gluLookAt();

	private:
	Quaternion m_Orientation;
	
	public:

        void gluLookAtv();

	void move (GLfloat x, GLfloat y, GLfloat z);
	void moveRelative (GLfloat x, GLfloat y, GLfloat z);

	void rotate (const Quaternion& q);

        void rotate(const Vector3& axis, const Radian& angle);


	void roll (const GLfloat angle); 
	void yaw (const GLfloat angle); 
	void pitch (const GLfloat angle);  

		
	};

M3D_END_NAMESPACE

#endif
