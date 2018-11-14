#pragma once

///////////////////////////////////////////////////////////////////////////////////////////
//XEngine
//Vec4


#ifndef Vector4_H
#define Vector4_H




namespace XEngine
{
	struct Vector2;
	struct Vector3;

	struct Vector4
	{
		Vector4();
		Vector4(float x, float y, float z, float w);
		Vector4(const Vector3& vec, float w);
		Vector4(const Vector4& vec);

		void clamp();
		float dot(Vector4& vec);
		void normalize();
		float magnitude();
		void zero();

		Vector4& operator= (const Vector4& obj);

		float operator[] (int i) const;
		float& operator[] (int i);

		bool operator== (const Vector4& obj) const;
		bool operator!= (const Vector4& obj) const;


		Vector4& operator+= (const Vector4& vec);
		Vector4& operator-= (const Vector4& vec);
		Vector4& operator*= (const Vector4& vec);
		Vector4& operator*= (float scale);
		Vector4& operator/= (const Vector4& vec);
		Vector4& operator/= (float scale);

		Vector4 operator+ (const Vector4& vec) const;
		Vector4 operator- (const Vector4& vec) const;
		Vector4 operator* (const Vector4& vec) const;
		Vector4 operator* (float scalar) const;
		Vector4 operator/ (const Vector4& vec) const;
		Vector4 operator/ (float scalar) const;
		Vector4 operator- () const;

		Vector3 xyz() const;
		Vector2 xy() const;

		unsigned int toARGB();
		unsigned int toRGBA();
		void fromARGB(unsigned int color);

		float x, y, z, w;
	};
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // !Vector4_H


