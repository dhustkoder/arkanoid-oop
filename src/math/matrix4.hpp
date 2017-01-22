#ifndef GPROJ_MATRIX4_HPP_
#define GPROJ_MATRIX4_HPP_
#include <math.h>
#include "math_types.hpp"
#include "vector3.hpp"


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
	Mat4 result;

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			result[i][j] = a[i][j] + b[i][j];

	return result;
}


inline Mat4 operator-(const Mat4& a, const Mat4& b)
{
	Mat4 result;

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			result[i][j] = a[i][j] - b[i][j];

	return result;
}


inline Mat4 operator*(const Mat4& a, const Mat4& b)
{
	Mat4 result;

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


inline bool operator==(const Mat4& a, const Mat4& b)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if (a[i][j] != b[i][j])
				return false;

	return true;
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
	return translation_mat4(v.x, v.y, v.z) * m;
}


inline Mat4 scale(Mat4 m, const Vec3& v)
{
	return identity_mat4(v.x, v.y, v.z) * m;
}


inline Mat4 rotate(const Mat4& m, const float radians, const Vec3& v)
{
	const float c = cosf(radians);
	const float s = sinf(radians);
	const Vec3 uni = normalize(v);
	const float x = uni.x, y = uni.y, z = uni.z;

	const Mat4 rotation {{
		{ c + (x*x) * (1 - c), x * y * (1 - c) - z * s,  x * z * (1 - c) + y * s, 0 },
		{ y * x * (1 - c) + z * s, c + (y*y) * (1 - c), y * z * (1 - c) - x * s, 0 },
		{ z * x * (1 - c) - y * s, z * y * (1 - c) + x * s, c + (z*z) * (1 - c), 0 },
		{ 0, 0, 0, 1 }
	}};

	return rotation * m;
}


inline Mat4 perspective(const float fov, const float aspect, const float near, const float far)
{
	const float tanfov = tanf(fov * 0.5f);
	Mat4 res {};

	res[0][0] = 1.0f / (tanfov * aspect);
	res[1][1] = 1.0f / tanfov;
	res[2][2] = - (far + near) / (far - near);
	res[2][3] = -1.0f;
	res[3][2] = - (2.0f * far * near) / (far - near);
	return res;
}


inline Mat4 look_at(const Vec3& eye, const Vec3& center, const Vec3& up)
{
	const Vec3 f = normalize(center - eye);
	const Vec3 s = normalize(cross(f, up));
	const Vec3 u = cross(s, f);

	Mat4 res = identity_mat4();

	res[0][0] = s.x;
	res[1][0] = s.y;
	res[2][0] = s.z;
	res[0][1] = u.x;
	res[1][1] = u.y;
	res[2][1] = u.z;
	res[0][2] = -f.x;
	res[1][2] = -f.y;
	res[2][2] = -f.z;
	res[3][0] = -dot(s, eye);
	res[3][1] = -dot(u, eye);
	res[3][2] = dot(f, eye);

	return res;
}


} // namespace gp
#endif

