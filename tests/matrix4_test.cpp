#include <stdio.h>
#include <math.h>
#include "matrix4.hpp"
#include "vector4.hpp"

using namespace gp;


void print(const char* const desc, const Mat4& m)
{
	const auto x = m[0];
	const auto y = m[1];
	const auto z = m[2];
	const auto t = m[3];

	printf("%s\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
	       desc,
	       x[0], x[1], x[2], x[3],
	       y[0], y[1], y[2], y[3],
	       z[0], z[1], z[2], z[3],
	       t[0], t[1], t[2], t[3]);
}


void print(const char* const desc, const Vec4& v)
{
	printf("%s\n%f %f %f %f\n", desc, v.x, v.y, v.z, v.w);
}


bool multiplications()
{
	constexpr Mat4 m {{
	  {-1.0,-0.9,-0.8,-0.7 },
	  {-0.6,-0.5,-0.4,-0.3 },
	  {-0.2,-0.1, 0.0, 0.1 },
	  { 0.2, 0.3, 0.4, 0.5 }
	}};

	constexpr Mat4 m2 {{
	  { 0.6, 0.7, 0.8, 0.9 },
	  { 1.0,-1.0,-0.9, 0.8 },
	  {-0.7,-0.6,-0.5,-0.4 },
	  {-0.3,-0.2,-0.1, 0.0 }
	}};


	Mat4 expect {{
		{-0.730, 0.820, 0.480,-1.300 },
		{-0.490, 0.380, 0.200,-0.780 },
		{-0.250,-0.060,-0.080,-0.260 },
		{-0.010,-0.500,-0.360, 0.260 }
	}};

	Mat4 res = m * m2;
	
	print("(M * M2) RES", res);
	print("EXPECTED", expect);

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			if (fabs(res[i][j] - expect[i][j]) > 0.00001)
				return false;



	constexpr Vec4 v {-1.0,-0.9,-0.8,-0.7};
	constexpr Vec4 vec_expect = { 2.940, 1.580, 0.220, -1.140 };

	const Vec4 vec_res = m * v;

	print("(M * V) RES", vec_res);
	print("EXPECT", vec_expect);

	if (fabs(vec_res.x - vec_expect.x) > 0.00001)
		return false;
	if (fabs(vec_res.y - vec_expect.y) > 0.00001)
		return false;
	if (fabs(vec_res.z - vec_expect.z) > 0.00001)
		return false;
	if (fabs(vec_res.w - vec_expect.w) > 0.00001)
		return false;

	return true;
}


int main()
{
	printf("MULTIPLICATION %s\n", multiplications() ? "PASSED" : "FAILED");
	return 0;
}
















