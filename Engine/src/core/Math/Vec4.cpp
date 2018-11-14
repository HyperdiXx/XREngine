
#include "../pch/ch.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

using namespace XEngine;

Vector4::Vector4()
{

}

XEngine::Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

XEngine::Vector4::Vector4(const Vector3 & vec, float w)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	this->w = w;
}

XEngine::Vector4::Vector4(const Vector4 & vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
}

void XEngine::Vector4::clamp()
{
	if (x > 1.0f)
		x = 1.0f;
	if (x < 0.0f)
		x = 0.0f;
	if (y > 1.0f)
		y = 1.0f;
	if (y < 0.0f)
		y = 0.0f;
	if (z > 1.0f)
		z = 0.0f;
	if (z < 0.0f)
		z = 0.0f;
	if (w > 1.0f)
		w = 1.0f;
	if (w < 0.0f)
		w = 0.0f;
}

float XEngine::Vector4::dot(Vector4 & vec)
{
	float v = 0.0f;

	v += x * vec.x;
	v += y * vec.y;
	v += z * vec.z;
	v += w * vec.w;

	return v;
}

void XEngine::Vector4::normalize()
{
	float n = 1.0f / magnitude();

	x *= n;
	y *= n;
	z *= n;
	w *= n;
}

float XEngine::Vector4::magnitude()
{
	float legth = 0.0f;

	legth += x * x;
	legth += y * y;
	legth += z * z;
	legth += w * w;

	return sqrt(legth);
}

void XEngine::Vector4::zero()
{
	x = y = z = w = 0.0f;
}

Vector4 & XEngine::Vector4::operator=(const Vector4 & obj)
{
	Vector4 r;
	return (r);
}

float XEngine::Vector4::operator[](int i) const
{
	if (i == 0)
		return x;
	if (i == 1)
		return y;
	if (i == 2)
		return z;
	return w;
}

float & XEngine::Vector4::operator[](int i)
{
	if (i == 0)
		return x;
	if (i == 1)
		return y;
	if (i == 2)
		return z;
	return w;
}

bool XEngine::Vector4::operator==(const Vector4 & vec) const
{
	if ((x - vec.x) * (x - vec.x) > 0.01f)
		return false;
	if ((y - vec.y) * (y - vec.y) > 0.01f)
		return false;

	if ((z - vec.z) * (z - vec.z) > 0.01f)
		return false;
	if ((w - vec.w) * (w - vec.w) > 0.01f)
		return false;
	
	return true;
}

bool XEngine::Vector4::operator!=(const Vector4 & vec) const
{
	return (!(*this == vec));
}

Vector4 & XEngine::Vector4::operator+=(const Vector4 & vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;

	return (*this);
}

Vector4 & XEngine::Vector4::operator-=(const Vector4 & vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	w -= vec.w;

	return (*this);
}

Vector4 & XEngine::Vector4::operator*=(const Vector4 & vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	w *= vec.w;

	return (*this);
}

Vector4 & XEngine::Vector4::operator*=(float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
	w *= scale;

	return (*this);
}

Vector4 & XEngine::Vector4::operator/=(const Vector4 & vec)
{
	x = vec.x != 0.0f ? x / vec.x : 0.0f;
	y = vec.y != 0.0f ? y / vec.y : 0.0f;
	z = vec.z != 0.0f ? z / vec.z : 0.0f;
	w = vec.w != 0.0f ? w / vec.w : 0.0f;

	return(*this);
}

Vector4 & XEngine::Vector4::operator/=(float scale)
{
	if (scale != 0.0f)
	{
		float fInvScalar = 1.0f / scale;
		x *= fInvScalar;
		y *= fInvScalar;
		z *= fInvScalar;
		w *= fInvScalar;
	}
	else
	{
		zero();
	}

	return(*this);
}

Vector4 XEngine::Vector4::operator+(const Vector4 & vec) const
{
	Vector4 s;

	s.x = x + vec.x;
	s.y = y + vec.y;
	s.z = z + vec.z;
	s.w = w + vec.w;

	return s;
}

Vector4 XEngine::Vector4::operator-(const Vector4 & vec) const
{
	Vector4 s;

	s.x = x - vec.x;
	s.y = y - vec.y;
	s.z = z - vec.z;
	s.w = w - vec.w;


	return s;
}

Vector4 XEngine::Vector4::operator*(const Vector4 & vec) const
{
	Vector4 v;

	v.x = x * vec.x;
	v.y = y * vec.y;
	v.z = z * vec.z;
	v.w = w * vec.w;

	return v;
}

Vector4 XEngine::Vector4::operator*(float scalar) const
{
	Vector4 scala;

	scala.x = x * scalar;
	scala.y = y * scalar;
	scala.z = z * scalar;
	scala.w = w * scalar;

	return scala;
}

Vector4 XEngine::Vector4::operator/(const Vector4 & vec) const
{
	Vector4 s;

	s.x = vec.x != 0.0f ? x / vec.x : 0.0f;
	s.y = vec.y != 0.0f ? y / vec.y : 0.0f;
	s.z = vec.z != 0.0f ? z / vec.z : 0.0f;
	s.w = vec.w != 0.0f ? w / vec.w : 0.0f;

	return s;
}

Vector4 XEngine::Vector4::operator/(float scalar) const
{
	Vector4 quot;
	if (scalar != 0.0f)
	{
		float fInvScalar = 1.0f / scalar;
		quot.x = x * fInvScalar;
		quot.y = y * fInvScalar;
		quot.z = z * fInvScalar;
		quot.w = w * fInvScalar;
	}
	else
	{
		quot.zero();
	}

	return quot;
}

Vector4 XEngine::Vector4::operator-() const
{
	Vector4 negative;

	negative.x = -x;
	negative.y = -y;
	negative.z = -z;
	negative.w = -w;


	return negative;
}

Vector3 XEngine::Vector4::xyz() const
{
	return Vector3(x, y, z);
}

Vector2 XEngine::Vector4::xy() const
{
	return Vector2(x, y);
}

unsigned int XEngine::Vector4::toARGB()
{
	unsigned int result = 0;

	clamp();

	result += (unsigned int)(255 * z);
	result += ((unsigned int)(255 * y) << 8);
	result += ((unsigned int)(255 * x) << 16);
	result += ((unsigned int)(255 * w) << 24);

	return(result);
}

unsigned int XEngine::Vector4::toRGBA()
{
	unsigned int result = 0;

	clamp();

	result += (unsigned int)(255 * w);
	result += ((unsigned int)(255 * z) << 8);
	result += ((unsigned int)(255 * y) << 16);
	result += ((unsigned int)(255 * x) << 24);

	return(result);
}

void XEngine::Vector4::fromARGB(unsigned int color)
{
	x = (float)((color & 0x00FF0000) >> 16) / (255.0f);
	y = (float)((color & 0x0000FF00) >> 8) / (255.0f);
	z = (float)((color & 0x000000FF)) / 255.0f;
	w = (float)((color & 0xFF000000) >> 24) / (255.0f);
}
