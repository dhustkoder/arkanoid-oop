#ifndef GPROJ_MATRIX4_HPP_
#define GPROJ_MATRIX4_HPP_
#include "math_types.hpp"

namespace gp {

	
constexpr Mat4 operator+(const Mat4& a, const Mat4& b)
{
	return {
		{ a.x.x + b.x.x, a.x.y + b.x.y, a.x.z + b.x.z, a.x.w + a.x.w },
		{ a.y.x + b.y.x, a.y.y + b.y.y, a.y.z + b.y.z, a.y.w + a.y.w },
		{ a.z.x + b.z.x, a.z.y + b.z.y, a.z.z + b.z.z, a.z.w + a.z.w },
		{ a.t.x + b.t.x, a.t.y + b.t.y, a.t.z + b.t.z, a.t.w + a.t.w }
	};
}


constexpr Mat4 operator-(const Mat4& a, const Mat4& b)
{
	return {
		{ a.x.x - b.x.x, a.x.y - b.x.y, a.x.z - b.x.z, a.x.w - a.x.w },
		{ a.y.x - b.y.x, a.y.y - b.y.y, a.y.z - b.y.z, a.y.w - a.y.w },
		{ a.z.x - b.z.x, a.z.y - b.z.y, a.z.z - b.z.z, a.z.w - a.z.w },
		{ a.t.x - b.t.x, a.t.y - b.t.y, a.t.z - b.t.z, a.t.w - a.t.w }
	};
}


constexpr Mat4 operator*(const Mat4& a, const Mat4& b)
{
	return {
		{
		 a.x.x * b.x.x + a.x.y * b.y.x + a.x.z * b.z.x + a.x.w * b.t.x,
		 a.x.x * b.x.y + a.x.y * b.y.y + a.x.z * b.z.y + a.x.w * b.t.y,
		 a.x.x * b.x.z + a.x.y * b.y.z + a.x.z * b.z.z + a.x.w * b.t.z,
		 a.x.x * b.x.w + a.x.y * b.y.w + a.x.z * b.z.w + a.x.w * b.t.w
		},

		{
		 a.y.x * b.x.x + a.y.y * b.y.x + a.y.z * b.z.x + a.y.w * b.t.x,
		 a.y.x * b.x.y + a.y.y * b.y.y + a.y.z * b.z.y + a.y.w * b.t.y,
		 a.y.x * b.x.z + a.y.y * b.y.z + a.y.z * b.z.z + a.y.w * b.t.z,
		 a.y.x * b.x.w + a.y.y * b.y.w + a.y.z * b.z.w + a.y.w * b.t.w
		},

		{
		 a.z.x * b.x.x + a.z.y * b.y.x + a.z.z * b.z.x + a.z.w * b.t.x,
		 a.z.x * b.x.y + a.z.y * b.y.y + a.z.z * b.z.y + a.z.w * b.t.y,
		 a.z.x * b.x.z + a.z.y * b.y.z + a.z.z * b.z.z + a.z.w * b.t.z,
		 a.z.x * b.x.w + a.z.y * b.y.w + a.z.z * b.z.w + a.z.w * b.t.w
		},

		{
		 a.t.x * b.x.x + a.t.y * b.y.x + a.t.z * b.z.x + a.t.w * b.t.x,
		 a.t.x * b.x.y + a.t.y * b.y.y + a.t.z * b.z.y + a.t.w * b.t.y,
		 a.t.x * b.x.z + a.t.y * b.y.z + a.t.z * b.z.z + a.t.w * b.t.z,
		 a.t.x * b.x.w + a.t.y * b.y.w + a.t.z * b.z.w + a.t.w * b.t.w
		}
	};
}


Mat4& operator+=(Mat4& a, const Mat4& b)
{
	a = a + b;
	return a;
}


Mat4& operator-=(Mat4& a, const Mat4& b)
{
	a = a - b;
	return a;
}


Mat4& operator*=(Mat4& a, const Mat4& b)
{
	a = a * b;
	return a;
}


}
#endif

