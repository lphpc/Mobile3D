
#include "camera.h"

M3D_BEGIN_NAMESPACE

    Camera::Camera() :
            m_centerx(0.0f),
            m_centery(0.0f),
            m_centerz(0.0f),
            m_upx(0.0f),
            m_upy(1.0f),
            m_upz(0.0f) {

        m_Orientation = Quaternion::IDENTITY;

    }

    Camera::~Camera() {
    }

    void Camera::setEye(GLfloat eyex, GLfloat eyey, GLfloat eyez) {
        m_eyex = eyex;
        m_eyey = eyey;
        m_eyez = eyez;
    }

    void Camera::setCenter(GLfloat centerx, GLfloat centery, GLfloat centerz) {
        m_centerx = centerx;
        m_centery = centery;
        m_centerz = centerz;
    }

    void Camera::setUp(GLfloat upx, GLfloat upy, GLfloat upz) {
        m_upx = upx;
        m_upy = upy;
        m_upz = upz;
    }

    void Camera::identf(GLfloat m[]) {
        memset(m, 0, sizeof m[0]*16);
        m[0] = m[5] = m[10] = m[15] = 1.0f;
    }

    void Camera::normalizef(float v[3]) {
        float r;

        r = (float)sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
        if (r == 0.0)
            return;
        r = 1.f/r;

        v[0] *= r;
        v[1] *= r;
        v[2] *= r;
    }

    void Camera::crossf(float v0[3], float v1[3], float r[3]) {
        r[0] = v0[1]*v1[2] - v0[2]*v1[1];
        r[1] = v0[2]*v1[0] - v0[0]*v1[2];
        r[2] = v0[0]*v1[1] - v0[1]*v1[0];
    }

    void Camera::gluLookAt() {
        GLfloat forward[3], side[3], up[3];
        GLfloat m[4][4];

        forward[0] = m_centerx - m_eyex;
        forward[1] = m_centery - m_eyey;
        forward[2] = m_centerz - m_eyez;

        normalizef(forward);

        up[0] = m_upx;
        up[1] = m_upy;
        up[2] = m_upz;

        crossf(forward, up, side);

        normalizef(side);
        crossf(side, forward, up);

        identf(&m[0][0]);
        m[0][0] = side[0];
        m[1][0] = side[1];
        m[2][0] = side[2];

        m[0][1] = up[0];
        m[1][1] = up[1];
        m[2][1] = up[2];

        m[0][2] = -forward[0];
        m[1][2] = -forward[1];
        m[2][2] = -forward[2];

        glMultMatrixf(&m[0][0]);
        glTranslatef(-m_eyex, -m_eyey, -m_eyez);
    }


    void Camera::gluLookAtv() {
        GLfloat m[4][4];

        identf(&m[0][0]);
	m_Orientation.createMatrix (&m[0][0]);

        glMultMatrixf(&m[0][0]);
        glTranslatef(-m_eyex, -m_eyey, -m_eyez);
    }






    void Camera::move(GLfloat x, GLfloat y, GLfloat z) {

        m_eyex += x;
        m_eyey += y;
        m_eyez += z;

    }

    void Camera::moveRelative(GLfloat x, GLfloat y, GLfloat z) {

	Vector3 vec (x, y, z);

        Vector3 trans = m_Orientation * vec;

        m_eyex += trans.x;
        m_eyey += trans.y;
        m_eyez += trans.z;

//        mPosition = mPosition + trans;

    }



    void Camera::rotate(const Quaternion& q)                                                                          
    {   
        // Note the order of the mult, i.e. q comes after                                                             
        m_Orientation = q * m_Orientation;
        
    } 

    void Camera::rotate(const Vector3& axis, const Radian& angle)                                                                          
    {   
        Quaternion q;
        q.FromAngleAxis(angle,axis);
        rotate(q);
    }       

    void Camera::roll (const GLfloat angle) //in radian
    {

	Degree d (angle);
	Radian r = Radian(d);


        Vector3 zAxis = m_Orientation * Vector3::UNIT_Z;
        rotate(zAxis, r);

    }

    void Camera::yaw (const GLfloat angle)  //in degree
    {
	Degree d (angle);
	Radian r = Radian(d);

        Vector3 yAxis;

        {
            // Rotate around local Y axis
            yAxis = m_Orientation * Vector3::UNIT_Y;
        }

        rotate(yAxis, r);



    }

    void Camera::pitch (const GLfloat angle)  //in radian
    {

	Degree d (angle);
	Radian r = Radian(d);

        Vector3 xAxis = m_Orientation * Vector3::UNIT_X;
        rotate(xAxis, r);

    }


M3D_END_NAMESPACE
