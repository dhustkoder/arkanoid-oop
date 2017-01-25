#ifndef GPROJ_VECTOR2_HPP_
#define GPROJ_VECTOR2_HPP_
#include <math.h>
#include "math_types.hpp"

namespace gp {


constexpr Vec2 operator+(const Vec2& a, const Vec2& b)
{
	return { a.x + b.x, a.y + b.y };
}


constexpr Vec2 operator-(const Vec2& a, const Vec2& b)
{
	return { a.x - b.x, a.y - b.y };
}


constexpr Vec2 operator*(const Vec2& a, const float scalar)
{
	return { a.x * scalar, a.y * scalar };
}


inline Vec2& operator+=(Vec2& a, const Vec2& b)
{
	a = a + b;
	return a;
}


inline Vec2& operator-=(Vec2& a, const Vec2& b)
{
	a = a - b;
	return a;
}


inline Vec2& operator*=(Vec2& a, const float scalar)
{
	a = a * scalar;
	return a;
}



inline bool operator==(const Vec2& a, const Vec2& b)
{
	if (fabs((a.x - b.x) + (a.y - b.y)) > 0.00001)
		return false;
	return true;
}


inline bool operator!=(const Vec2& a, const Vec2& b)
{
	return !(a == b);
}


inline float dot(const Vec2& a, const Vec2& b)
{
	return (a.x * b.x) + (a.y * b.y);
}


inline float length(const Vec2& v)
{
	return sqrtf(dot(v, v));
}


inline Vec2 normalize(const Vec2& v)
{
	const float len = length(v);
	return { v.x / len, v.y / len };
}


} // namespace gp
#endif

