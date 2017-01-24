#ifndef GPROJ_VECTOR3_HPP_
#define GPROJ_VECTOR3_HPP_
#include <math.h>
#include "math_types.hpp"

namespace gp {


constexpr Vec3 operator+(const Vec3& a, const Vec3& b)
{
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}


constexpr Vec3 operator-(const Vec3& a, const Vec3& b)
{
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}


constexpr Vec3 operator*(const Vec3& a, const float scalar)
{
	return { a.x * scalar, a.y * scalar, a.z * scalar };
}


inline Vec3& operator+=(Vec3& a, const Vec3& b)
{
	a = a + b;
	return a;
}


inline Vec3& operator-=(Vec3& a, const Vec3& b)
{
	a = a - b;
	return a;
}


inline Vec3& operator*=(Vec3& a, const float scalar)
{
	a = a * scalar;
	return a;
}


inline bool operator==(const Vec3& a, const Vec3& b)
{
	if (fabs(a.x - b.x) > 0.00001)
		return false;
	else if (fabs(a.y - b.y) > 0.00001)
		return false;
	else if (fabs(a.z - b.z) > 0.00001)
		return false;

	return true;
}


inline bool operator!=(const Vec3& a, const Vec3& b)
{
	return !(a == b);
}


inline Vec3 cross(const Vec3& a, const Vec3& b)
{
	return {
		(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z),
		(a.x * b.y) - (a.y * b.x)
	};
}


inline float dot(const Vec3& a, const Vec3& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}


inline float length(const Vec3& v)
{
	return sqrtf(dot(v, v));	
}


inline Vec3 normalize(const Vec3& v)
{
	const float len = length(v);
	return { v.x / len, v.y / len, v.z / len };
}


} // namespace gp
#endif

