#pragma once


#ifndef MAT3_H
#define MAT3_H

#include "Vec3.h"

namespace XEngine
{
	struct Mat3
	{
		Mat3();
		Mat3(bool zero);
		Mat3(const Mat3& mat);
		Mat3(float m11, float m12, float m13,
			float m21, float m22, float m23,
			float m31, float m32, float m33);


		void RotationX(float fRadians);
		void RotationY(float fRadians);
		void RotationZ(float fRadians);
		void Rotation(Vector3& Rot);
		void RotationZYX(Vector3& Rot);
		void RotationEuler(Vector3& Axis, float Angle);
		void Orthonormalize();

		void MakeZero();
		void MakeIdentity();
		void MakeTranspose();

		Mat3 Zero();
		Mat3 Identity();
		Mat3 Transpose();

		// Operators
		Mat3& operator= (const Mat3& Matrix);

		// member access
		float operator() (int iRow, int iCol) const;
		float& operator() (int iRow, int iCol);
		float operator[] (int iPos) const;
		float& operator[] (int iPos);

		void SetRow(int iRow, const Vector3& Vector);
		Vector3 GetRow(int iRow) const;
		void SetColumn(int iCol, const Vector3& Vector);
		Vector3 GetColumn(int iCol) const;

		// comparison
		bool operator== (const Mat3& Matrix) const;
		bool operator!= (const Mat3& Matrix) const;

		// arithmetic operations
		Mat3 operator+ (const Mat3& Matrix) const;
		Mat3 operator- (const Mat3& Matrix) const;
		Mat3 operator* (const Mat3& Matrix) const;
		Mat3 operator* (float fScalar) const;
		Mat3 operator/ (float fScalar) const;
		Mat3 operator- () const;

		// arithmetic updates
		Mat3& operator+= (const Mat3& Matrix);
		Mat3& operator-= (const Mat3& Matrix);
		Mat3& operator*= (const Mat3& Matrix);
		Mat3& operator*= (float fScalar);
		Mat3& operator/= (float fScalar);

		// matrix - vector operations
		Vector3 operator* (const Vector3& rkV) const;  // M * v

	protected:
		float m_afEntry[3 * 3];

		static int I(int iRow, int iCol); // iRow*N + iCol




	};
}
#endif // !MAT3_H
