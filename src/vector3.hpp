#ifndef GPROJ_VECTOR3_HPP_
#define GPROJ_VECTOR3_HPP_
#include "math_types.h"

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


Vec3& operator+=(Vec3& a, const Vec3& b)
{
	a = a + b;
	return a;
}


Vec3& operator-=(Vec3& a, const Vec3& b)
{
	a = a - b;
	return a;
}


Vec3& operator*=(Vec3& a, const float scalar)
{
	a = a * scalar;
	return a;
}


}
#endif

