
#ifndef _WORLD_H
#define _WORLD_H

#include "m3d.h"
#include "camera.h"
#include "light.h"

M3D_BEGIN_NAMESPACE

	class World {
	private:

        int     m_width;
        int     m_height;
        GLfloat m_bgred;
        GLfloat m_bggreen;
        GLfloat m_bgblue;
        GLfloat m_bgalpha;
        GLfloat m_fovy;
        GLfloat m_znear;
        GLfloat m_zfar;
        Camera  *m_camera;
        Light   *m_light;

	private:
		void gluPerspective ();
		bool initGL ();


	public:
		World ();
        ~World();

        void setCamera(Camera* camera);
        void setLight(Light* light);
        void setBgColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
        bool init();
        void setSize(int width, int height);
        void setPerspective(GLfloat fovy, GLfloat znear, GLfloat zfar);
        int getWidth();
        int getHeight();

        void prepareRender();
        void finishRender();

	};


M3D_END_NAMESPACE

#endif
