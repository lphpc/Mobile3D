
#ifndef M3D_LIGHT_H_
#define M3D_LIGHT_H_

#include "m3d.h"

M3D_BEGIN_NAMESPACE

    class Light {

    private:
        GLfloat* m_position;
        GLfloat* m_ambient;
        GLfloat* m_diffuse;
        GLfloat* m_specular;
        GLfloat* m_emission;

    public:
        Light();

        ~Light();

        void setPosition(GLfloat* position);
        void setAmbient(GLfloat* ambient);
        void setDiffuse(GLfloat* diffuse);
        void setSpecular(GLfloat* specular);
        void setEmission(GLfloat* emission);

        void initLight();
    };

M3D_END_NAMESPACE

#endif /* M3D_LIGHT_H_ */
