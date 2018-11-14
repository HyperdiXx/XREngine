
#include "../pch/ch.h"
#include "Vec3.h"

using namespace XEngine;


Vector3::Vector3()
{

}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = x;
	this->z = x;
}

Vector3::Vector3(const Vector3& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}


float Vector3::dot(const Vector3& vec) const
{
	float r = 0.0f;

	r = this->x * vec.x;
	r += this->y * vec.y;
	r += this->z * vec.z;

	return r;
}

void Vector3::clamp()
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
		z = 1.0f;
	if (z < 0.0f)
		z = 0.0f;
}

void Vector3::zero()
{
	x = y = z = 0.0f;
}

float Vector3::magnitude()
{
	float length = 0.0f;

	length += x * x;
	length += y * y;
	length += z * z;

	return (sqrt(length));
}

void Vector3::normalize()
{
	float m = magnitude();
	if (0.0f == m) 
		m = 0.0001f;

	float iMag = (1.0f / m);

	x *= iMag;
	y *= iMag;
	z *= iMag;
}

Vector3 XEngine::Vector3::perpendicular()
{
	float xAbs = fabs(x);
	float yAbs = fabs(y);
	float zAbs = fabs(z);
	float minVal = min(min(xAbs, yAbs), zAbs);

	if (xAbs == minVal)
		return cross(Vector3(1.0f, 0.0f, 0.0f));
	else if (yAbs == minVal)
		return cross(Vector3(0.0f, 1.0f, 0.0f));
	else
		return cross(Vector3(0.0f, 0.0f, 1.0f));
}

Vector3 Vector3::cross(const Vector3& vec) const
{
	Vector3 rV;
	
	rV.x = y * vec.z - z * vec.y;
	rV.y = z * vec.x - x * vec.z;
	rV.z = x * vec.y - y * vec.x;

	return rV;
}

float Vector3::magnitude(const Vector3 & vector)
{
	return sqrt(dot(vector, vector));
}

Vector3 Vector3::clamp(const Vector3 & vector)
{
	Vector3 v = vector;
	v.clamp();
	return v;
}

Vector3 Vector3::cross(const Vector3 & vec1, const Vector3 & vec2)
{
	return vec1.cross(vec2);
}

float Vector3::dot(const Vector3 & vec1, const Vector3 & vec2)
{
	return vec1.dot(vec2);
}

float Vector3::lengthSq(const Vector3 & vec)
{
	return dot(vec, vec);
}

Vector3 Vector3::normalize(const Vector3 & vec)
{
	Vector3 v = vec;
	v.normalize();

	return v;
}

Vector3 Vector3::perpendicular(const Vector3 & vec)
{
	Vector3 v = vec;
	return v.perpendicular();
}

Vector3 Vector3::random()
{
	float x = static_cast<float>((double)rand() / RAND_MAX) * 2.f - 1.0f;
	float y = static_cast<float>((double)rand() / RAND_MAX) * 2.f - 1.0f;
	float z = static_cast<float>((double)rand() / RAND_MAX) * 2.f - 1.0f;

	Vector3 r = Vector3(x, y, z);
	r.normalize();

	return r;
}

Vector3& Vector3::operator=(const Vector3& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;

	return (*this);
}

float& Vector3::operator[](int i)
{
	if (i == 0)
		return (x);
	if (i == 1)
		return (y);
	return (z);
}

float Vector3::operator[](int i) const
{
	if (i == 0)
		return (x);
	if (i == 1)
		return (y);
	return (z);
}

bool Vector3::operator==(const Vector3& vec) const
{
	if ((x - vec.x) * (x - vec.x) > 0.01f)
		return false;
	if ((y - vec.y) * (y - vec.y) > 0.01f)
		return false;
	if ((z - vec.z) * (z - vec.z) > 0.01f)
		return false;

	return true;
}


bool Vector3::operator!=(const Vector3& vec) const
{
	return (!(*this == vec));
}


Vector3 Vector3::operator+(const Vector3 & vec) const
{
	Vector3 r;

	r.x = x + vec.x;
	r.y = y + vec.y;
	r.z = z + vec.z;
	
	return (r);
}

Vector3 Vector3::operator-(const Vector3 & vec) const
{
	Vector3 d;

	d.x = x - vec.x;
	d.y = y - vec.y;
	d.z = z - vec.z;
	
	return d;
}

Vector3 XEngine::Vector3::operator*(const Vector3 & vec) const
{
	Vector3 s;

	s.x = x * vec.x;
	s.y = y * vec.y;
	s.z = z * vec.z;

	return (s);
}

Vector3 Vector3::operator*(float scalar)const
{
	Vector3 s;

	s.x = x * scalar;
	s.y = y * scalar;
	s.z = z * scalar;

	return s;
}

Vector3 XEngine::Vector3::operator/(const Vector3 & vec) const
{
	Vector3 q;

	q.x = vec.x != 0.0f ? x / vec.x : 0.0f;
	q.y = vec.y != 0.0f ? y / vec.y : 0.0f;
	q.z = vec.z != 0.0f ? z / vec.z : 0.0f;

	return q;
}

Vector3 XEngine::Vector3::operator/(float scalar) const
{
	Vector3 q;

	if (scalar != 0.0f)
	{
		float iScalar = 1.0f / scalar;

		q.x = x * iScalar;
		q.y = y * iScalar;
		q.z = z * iScalar;
	}
	else
	{
		q.zero();
	}


	return q;
}

Vector3 XEngine::Vector3::operator-() const
{
	Vector3 s;

	s.x = -x;
	s.y = -y;
	s.z = -z;

	return s;
}


Vector3 & XEngine::Vector3::operator+=(const Vector3 & vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
}

Vector3 & XEngine::Vector3::operator-=(const Vector3 & vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
}

Vector3 & XEngine::Vector3::operator*=(const Vector3 & vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;

	return(*this);
}

Vector3 & XEngine::Vector3::operator*=(float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;

	return(*this);
}

Vector3 & XEngine::Vector3::operator/=(const Vector3 & vec)
{
	x = vec.x != 0.0f ? x / vec.x : 0.0f;
	y = vec.y != 0.0f ? y / vec.y : 0.0f;
	z = vec.z != 0.0f ? z / vec.z : 0.0f;

	return(*this);
}

Vector3 & XEngine::Vector3::operator/=(float scale)
{
	if (scale != 0.0f)
	{
		float fInvScalar = 1.0f / scale;
		x *= fInvScalar;
		y *= fInvScalar;
		z *= fInvScalar;
	}
	else
	{
		zero();
	}

	return(*this);
}

