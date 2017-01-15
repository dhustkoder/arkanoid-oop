#ifndef GPROJ_MATRIX4_HPP_
#define GPROJ_MATRIX4_HPP_
#include "math_types.hpp"

namespace gp {


constexpr const float (&Mat4::operator[](int index) const)[4]
{
	return data[index];
}


constexpr float (&Mat4::operator[](int index))[4]
{
	return const_cast<float(&)[4]>(static_cast<const Mat4&>(*this)[index]);
}

	
constexpr Mat4 operator+(const Mat4& a, const Mat4& b)
{
	Mat4 result {};

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			result[i][j] = a[i][j] + b[i][j];

	return result;
}


constexpr Mat4 operator-(const Mat4& a, const Mat4& b)
{
	Mat4 result {};

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			result[i][j] = a[i][j] - b[i][j];

	return result;
}


constexpr Mat4 operator*(const Mat4& a, const Mat4& b)
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




} // namespace gp
#endif

