#ifndef GPROJ_VECTOR2_HPP_
#define GPROJ_VECTOR2_HPP_
#include "math_types.h"

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


Vec2& operator+=(Vec2& a, const Vec2& b)
{
	a = a + b;
	return a;
}


Vec2& operator-=(Vec2& a, const Vec2& b)
{
	a = a - b;
	return a;
}


Vec2& operator*=(Vec2& a, const float scalar)
{
	a = a * scalar;
	return a;
}


} // namespace gp
#endif

