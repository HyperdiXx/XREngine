#pragma once
//////////////////////////////////////////////
// Math
// XEngine
//////////////////////////////////////////////


#ifndef VECTOR_H
#define VECTOR_H

namespace XEngine
{
	struct Vector3
	{
		Vector3();
		Vector3(float x, float y, float z);
		Vector3(const Vector3& obj);

		float dot(const Vector3& obj) const;
		Vector3 cross(const Vector3& obj) const;
		void clamp();
		void zero();
		float magnitude();
		void normalize();
		Vector3 perpendicular();

		static float magnitude(const Vector3& vector);
		static Vector3 clamp(const Vector3& vector);
		static Vector3 cross(const Vector3& vec1, const Vector3& vec2);
		static float dot(const Vector3& vec1, const Vector3& vec2);
		static float lengthSq(const Vector3& vec);
		static Vector3 normalize(const Vector3& vec);
		static Vector3 perpendicular(const Vector3& vec);
		static Vector3 random();

		Vector3& operator= (const Vector3& obj);

		float operator[] (int i) const;
		float& operator[] (int i);

		bool operator== (const Vector3& obj) const;
		bool operator!= (const Vector3& obj) const;


		Vector3& operator+= (const Vector3& vec);
		Vector3& operator-= (const Vector3& vec);
		Vector3& operator*= (const Vector3& vec);
		Vector3& operator*= (float scale);
		Vector3& operator/= (const Vector3& vec);
		Vector3& operator/= (float scale);

		Vector3 operator+ (const Vector3& vec) const;
		Vector3 operator- (const Vector3& vec) const;
		Vector3 operator* (const Vector3& vec) const;
		Vector3 operator* (float scalar) const;
		Vector3 operator/ (const Vector3& vec) const;
		Vector3 operator/ (float scalar) const;
		Vector3 operator- () const;

		float x, y, z;

	};
}
////////////////////////////////////////////////////////////////////////////////////////
#endif // !VECTOR_H

