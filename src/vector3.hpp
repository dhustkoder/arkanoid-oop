#ifndef GPROJ_VECTOR3_HPP_
#define GPROJ_VECTOR3_HPP_
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


inline float length(const Vec3& v)
{
	return sqrtf((v.x*v.x) + (v.y*v.y) + (v.z*v.z));	
}


inline Vec3 normalize(const Vec3& v)
{
	const float len = length(v);
	return { v.x/len, v.y/len, v.z/len };
}


} // namespace gp
#endif

