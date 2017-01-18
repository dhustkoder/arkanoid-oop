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


inline Vec4 operator*(const Mat4& m, const Vec4& v)
{
	return {
	  m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
	  m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
	  m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
	  m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w,
	};
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

