

#include "world.h"

M3D_BEGIN_NAMESPACE

    World::World() :
            m_bgred(0.0f),
            m_bggreen(0.0f),
            m_bgblue(0.0f),
            m_bgalpha(0.0f),
            m_fovy(60.0f),
            m_znear(1.0f),
            m_zfar(1000.0f){

		m_camera = NULL;
		m_light = NULL;

	
			
    }

    World::~World() {
    }

    void World::setBgColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
        m_bgred = red;
        m_bggreen = green;
        m_bgblue = blue;
        m_bgalpha = alpha;
    }

    void World::setCamera(Camera* camera) {
        m_camera = camera;
    }

    void World::setLight(Light* light) {
        m_light = light;
    }


    bool World::initGL() {
        // Initialize viewport and projection.
        glViewport( 0, 0, m_width, m_height );

        //set the matrix mode
        gluPerspective();

        //reset the matrix mode
        glMatrixMode(GL_MODELVIEW); //GL_PROJECTION,GL_MODELVIEW
        glLoadIdentity();

        // Set the screen background color.
        glClearColor(m_bgred, m_bggreen, m_bgblue, m_bgalpha);

        // set some init status
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glShadeModel(GL_SMOOTH);//GL_SMOOTH,GL_FLAT
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_FRONT);

        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //GL_FASTEST GL_NICEST
#ifdef DEBUG
        printf("********GL info********\n");
        printf("GL_VENDOR\t: %s\n", glGetString(GL_VENDOR));
        printf("GL_RENDERER\t: %s\n", glGetString(GL_RENDERER));
        printf("GL_VERSION\t: %s\n", glGetString(GL_VERSION));
        printf("GL_EXTENSIONS\t: %s\n", glGetString(GL_EXTENSIONS));
#endif
        return true;
    }

    bool World::init() {
        initGL();
        return true;

	}

    void World::setSize(int width, int height) {
        m_width = width;
        m_height = height;
        //after resize screen, call initGL() again
        initGL();
    }

    int World::getWidth() {
        return m_width;
    }

    int World::getHeight() {
        return m_height;
    }

    void World::setPerspective(GLfloat fovy, GLfloat znear, GLfloat zfar) {
        m_fovy = fovy;
        m_znear = znear;
        m_zfar = zfar;
    }


    void World::gluPerspective() {
        // Start in projection mode.
        GLfloat xmin, xmax, ymin, ymax;
        GLfloat aspect = (GLfloat)m_width / (GLfloat)m_height;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        ymax = (float) (m_znear * tan(m_fovy * M_PI / 360.0));
        ymin = -ymax;
        xmin = ymin * aspect;
        xmax = ymax * aspect;

#ifdef DEBUG
        printf("glFrustumf()\t: %.3f, %.3f, %.3f, %.3f, %.3f, %.3f\n", xmin, xmax, ymin, ymax, m_znear, m_zfar);
#endif

#ifdef OPENGL
        glFrustum(xmin, xmax, ymin, ymax, m_znear, m_zfar);
#else
        glFrustumf(xmin, xmax, ymin, ymax, m_znear, m_zfar);
#endif
    }


    void World::prepareRender() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        m_camera->gluLookAtv();
/*
        if (m_fog != NULL) {
            glEnable(GL_FOG);
            m_fog->initFog();
        }

*/
        if (m_light != NULL) {
            glEnable(GL_LIGHTING);
            m_light->initLight();
        }
    }

    void World::finishRender() {
        //eglSwapBuffers(m_display, m_surface);
    }



M3D_END_NAMESPACE
