#pragma once


//ROW MAJOR MATRIX

#ifndef MAT4_H
#define MAT4_H



#include "Mat3.h"
#include "Vec4.h"

namespace XEngine
{
	struct Mat4
	{
		Mat4();
		Mat4(bool Zero);
		Mat4(const Mat4& Matrix);
		Mat4(float f11, float f12, float f13, float f14,
			float f21, float f22, float f23, float f24,
			float f31, float f32, float f33, float f34,
			float f41, float f42, float f43, float f44);
		Mat4 Inverse() const;

		void RotateX(float radians);
		void RotateY(float radians);
		void RotateZ(float radians);

		void Translate(float x, float y, float z);
		void Scale(float scale);

		Vector3 GetBasisX() const;
		Vector3 GetBasisY() const;
		Vector3 GetBasisZ() const;

		Vector3 GetTranslation() const;
		
		void SetRotation(const Mat3& Rot);
		void SetTranslation(const Vector3& Trans);

		~Mat4();
	};
}
#endif
