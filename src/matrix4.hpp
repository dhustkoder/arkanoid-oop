#ifndef GPROJ_MATRIX4_HPP_
#define GPROJ_MATRIX4_HPP_
#include <math.h>
#include "math_types.hpp"

namespace gp {

inline const float (&Mat4::operator[](int index) const)[4]
{
	return data[index];
}


inline float (&Mat4::operator[](int index))[4]
{
	return const_cast<float(&)[4]>(static_cast<const Mat4&>(*this)[index]);
}

	
inline Mat4 operator+(const Mat4& a, const Mat4& b)
{
	Mat4 result {};

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			result[i][j] = a[i][j] + b[i][j];

	return result;
}


inline Mat4 operator-(const Mat4& a, const Mat4& b)
{
	Mat4 result {};

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			result[i][j] = a[i][j] - b[i][j];

	return result;
}


inline Mat4 operator*(const Mat4& a, const Mat4& b)
{
	Mat4 result {};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result[i][j] = a[i][0] * b[0][j] +
			               a[i][1] * b[1][j] +
				       a[i][2] * b[2][j] +
				       a[i][3] * b[3][j];
		}
	}

	return result;
}


inline Mat4& operator+=(Mat4& a, const Mat4& b)
{
	a = a + b;
	return a;
}


inline Mat4& operator-=(Mat4& a, const Mat4& b)
{
	a = a - b;
	return a;
}


inline Mat4& operator*=(Mat4& a, const Mat4& b)
{
	a = a * b;
	return a;
}


inline Mat4 identity_mat4(const float x = 1, const float y = 1, const float z = 1, const float w = 1)
{
	return {{
	         { x, 0, 0, 0 },
	         { 0, y, 0, 0 },
		 { 0, 0, z, 0 },
		 { 0, 0, 0, w } 
	}};
}


inline Mat4 translation_mat4(const float x = 1, const float y = 1, const float z = 1)
{
	return {{
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ x, y, z, 1 }
	}};
}


inline Mat4 translate(const Mat4& m, const Vec3& v)
{
	return m * translation_mat4(v.x, v.y, v.z);
}


inline Mat4 scale(Mat4 m, const Vec3& v)
{
	return m * identity_mat4(v.x, v.y, v.z);
}


inline Mat4 rotate_z(const Mat4& m, const float radians)
{
	const auto c = cosf(radians);
	const auto s = sinf(radians);

	Mat4 tmp = identity_mat4();
	tmp[0][0] = c;
	tmp[0][1] = -s;
	tmp[1][0] = s;
	tmp[1][1] = c;

	return m * tmp;
}


inline Mat4 rotate(const Mat4& m, const float radians, const Vec3& v)
{
	const float c = cosf(radians);
	const float s = sinf(radians);
	const float x = v.x, y = v.y, z = v.z;

	const Mat4 tmp {{
		{ c + (x*x) * (1 - c), x * y * (1 - c) - z * s,  x * z * (1 - c) + y * s, 0 },
		{ y * x * (1 - c) + z * s, c + (y*y) * (1 - c), y * z * (1 - c) - x * s, 0 },
		{ z * x * (1 - c) - y * s, z * y * (1 - c) + x * s, c + (z*z) * (1 - c), 0 },
		{ 0, 0, 0, 1 }
	}};

	return tmp * m;
}


} // namespace gp
#endif

