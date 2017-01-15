#ifndef GPROJ_VECTOR4_HPP_
#define GPROJ_VECTOR4_HPP_
#include "math_types.hpp"


namespace gp {


constexpr Vec4 operator+(const Vec4& a, const Vec4& b)
{
	return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}


constexpr Vec4 operator-(const Vec4& a, const Vec4& b)
{
	return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}


constexpr Vec4 operator*(const Vec4& a, const float scalar)
{
	return { a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar };
}


inline Vec4& operator+=(Vec4& a, const Vec4& b)
{
	a = a + b;
	return a;
}


inline Vec4& operator-=(Vec4& a, const Vec4& b)
{
	a = a - b;
	return a;
}


inline Vec4& operator*=(Vec4& a, const float scalar)
{
	a = a * scalar;
	return a;
}




} // namespace gp
#endif

