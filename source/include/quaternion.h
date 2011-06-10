/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/
*/

#ifndef __M3D_Quaternion_H__
#define __M3D_Quaternion_H__

#include "m3d.h"
//#include "OgrePrerequisites.h"
#include "m3dmath.h"
#include "vector3.h"

M3D_BEGIN_NAMESPACE

    /** Implementation of a Quaternion, i.e. a rotation around an axis.
    */
    class Quaternion
    {
    public:
        inline Quaternion (
            Real fW = 1.0,
            Real fX = 0.0, Real fY = 0.0, Real fZ = 0.0)
		{
			w = fW;
			x = fX;
			y = fY;
			z = fZ;
		}
        inline Quaternion (const Quaternion& rkQ)
		{
			w = rkQ.w;
			x = rkQ.x;
			y = rkQ.y;
			z = rkQ.z;
		}
/*
        /// Construct a quaternion from a rotation matrix
        inline Quaternion(const Matrix3& rot)
        {
            this->FromRotationMatrix(rot);
        }
*/
        /// Construct a quaternion from an angle/axis
        inline Quaternion(const Radian& rfAngle, const Vector3& rkAxis)
        {
            this->FromAngleAxis(rfAngle, rkAxis);
        }
#ifndef OGRE_FORCE_ANGLE_TYPES
        inline Quaternion(const Real& rfAngle, const Vector3& rkAxis)
		{
			this->FromAngleAxis(rfAngle, rkAxis);
		}
#endif//OGRE_FORCE_ANGLE_TYPES
        /// Construct a quaternion from 3 orthonormal local axes
        inline Quaternion(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
        {
            this->FromAxes(xAxis, yAxis, zAxis);
        }
        /// Construct a quaternion from 3 orthonormal local axes
        inline Quaternion(Vector3* akAxis)
        {
            this->FromAxes(akAxis);
        }
/*
        void FromRotationMatrix (const Matrix3& kRot);
        void ToRotationMatrix (Matrix3& kRot) const;
*/
        void FromAngleAxis (const Radian& rfAngle, const Vector3& rkAxis);
        void ToAngleAxis (Radian& rfAngle, Vector3& rkAxis) const;
        inline void ToAngleAxis (Degree& dAngle, Vector3& rkAxis) const {
            Radian rAngle;
            ToAngleAxis ( rAngle, rkAxis );
            dAngle = rAngle;
        }
#ifndef OGRE_FORCE_ANGLE_TYPES
        inline void FromAngleAxis (const Real& rfAngle, const Vector3& rkAxis) {
			FromAngleAxis ( Angle(rfAngle), rkAxis );
		}
        inline void ToAngleAxis (Real& rfAngle, Vector3& rkAxis) const {
			Radian r;
			ToAngleAxis ( r, rkAxis );
			rfAngle = r.valueAngleUnits();
		}
#endif//OGRE_FORCE_ANGLE_TYPES
        void FromAxes (const Vector3* akAxis);
        void FromAxes (const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);
        void ToAxes (Vector3* akAxis) const;
        void ToAxes (Vector3& xAxis, Vector3& yAxis, Vector3& zAxis) const;
        /// Get the local x-axis
        Vector3 xAxis(void) const;
        /// Get the local y-axis
        Vector3 yAxis(void) const;
        /// Get the local z-axis
        Vector3 zAxis(void) const;

        inline Quaternion& operator= (const Quaternion& rkQ)
		{
			w = rkQ.w;
			x = rkQ.x;
			y = rkQ.y;
			z = rkQ.z;
			return *this;
		}
        Quaternion operator+ (const Quaternion& rkQ) const;
        Quaternion operator- (const Quaternion& rkQ) const;
        Quaternion operator* (const Quaternion& rkQ) const;
        Quaternion operator* (Real fScalar) const;
/*
        //delete _Ogre
        friend Quaternion operator* (Real fScalar,
            const Quaternion& rkQ);
*/
        Quaternion operator- () const;
        inline bool operator== (const Quaternion& rhs) const
		{
			return (rhs.x == x) && (rhs.y == y) &&
				(rhs.z == z) && (rhs.w == w);
		}

        // functions of a quaternion
        Real Dot (const Quaternion& rkQ) const;  // dot product
        Real Norm () const;  // squared-length
        /// Normalises this quaternion, and returns the previous length
        Real normalise(void); 
        Quaternion Inverse () const;  // apply to non-zero quaternion
        Quaternion UnitInverse () const;  // apply to unit-length quaternion
        Quaternion Exp () const;
        Quaternion Log () const;

        // rotation of a vector by a quaternion
        Vector3 operator* (const Vector3& rkVector) const;

   		/// Calculate the local roll element of this quaternion
		Radian getRoll(void) const;
   		/// Calculate the local pitch element of this quaternion
		Radian getPitch(void) const;
   		/// Calculate the local yaw element of this quaternion
		Radian getYaw(void) const;		
	    // spherical linear interpolation
        static Quaternion Slerp (Real fT, const Quaternion& rkP,
            const Quaternion& rkQ, bool shortestPath = false);

        static Quaternion SlerpExtraSpins (Real fT,
            const Quaternion& rkP, const Quaternion& rkQ,
            int iExtraSpins);

        // setup for spherical quadratic interpolation
        static void Intermediate (const Quaternion& rkQ0,
            const Quaternion& rkQ1, const Quaternion& rkQ2,
            Quaternion& rka, Quaternion& rkB);

        // spherical quadratic interpolation
        static Quaternion Squad (Real fT, const Quaternion& rkP,
            const Quaternion& rkA, const Quaternion& rkB,
            const Quaternion& rkQ, bool shortestPath = false);

        // normalised linear interpolation - faster but less accurate (non-constant rotation velocity)
        static Quaternion nlerp(Real fT, const Quaternion& rkP, 
            const Quaternion& rkQ, bool shortestPath = false);

        // cutoff for sine near zero
        static const Real ms_fEpsilon;

        // special values
        static const Quaternion ZERO;
        static const Quaternion IDENTITY;

        Real w, x, y, z;

        /** Function for writing to a stream.
        */
/*
        inline _OgreExport friend std::ostream& operator <<
            ( std::ostream& o, const Quaternion& q )
        {
            o << "Quaternion(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
            return o;
        }
*/

    	void createMatrix (GLfloat *pMatrix);

    };

M3D_END_NAMESPACE




#endif 
