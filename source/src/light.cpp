
#include "light.h"

M3D_BEGIN_NAMESPACE

    Light::Light() :
            m_position(NULL),
            m_ambient(NULL),
            m_diffuse(NULL),
            m_specular(NULL),
            m_emission(NULL) {
    }

    Light::~Light() {
    }

    void Light::setPosition(GLfloat* position) {
        m_position = position;
    }

    void Light::setAmbient(GLfloat* ambient) {
        m_ambient = ambient;
    }

    void Light::setDiffuse(GLfloat* diffuse) {
        m_diffuse = diffuse;
    }

    void Light::setSpecular(GLfloat* specular) {
        m_specular = specular;
    }

    void Light::setEmission(GLfloat* emission) {
        m_emission = emission;
    }

    void Light::initLight() {

        if (m_position != NULL)
            glLightfv(GL_LIGHT0, GL_POSITION, m_position);

        if (m_ambient != NULL)
            glLightfv(GL_LIGHT0, GL_AMBIENT, m_ambient);

        if (m_diffuse != NULL)
            glLightfv(GL_LIGHT0, GL_DIFFUSE, m_diffuse);

        if (m_specular != NULL)
            glLightfv(GL_LIGHT0, GL_SPECULAR, m_specular);

        if (m_emission != NULL)
            glLightfv(GL_LIGHT0, GL_EMISSION, m_emission);


        //GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
        //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);

        glEnable(GL_LIGHT0);
    }


M3D_END_NAMESPACE
