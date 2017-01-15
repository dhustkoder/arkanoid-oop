#include <stdio.h>
#include "matrix4.hpp"
#include "vector4.hpp"

void print(const char* const disc, const gp::Mat4& m)
{
	const auto x = m[0];
	const auto y = m[1];
	const auto z = m[2];
	const auto t = m[3];

	printf("%s\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
	       disc,
	       x[0], x[1], x[2], x[3],
	       y[0], y[1], y[2], y[3],
	       z[0], z[1], z[2], z[3],
	       t[0], t[1], t[2], t[3]);
}



int main()
{
	using namespace gp;

	constexpr const Mat4 a {{
	  { 1.1, 2.2, 3.3, 4.4 },
	  { 5.5, 6.6, 7.7, 8.8 },
	  { 9.9, 10.10, 11.11, 12.12 },
	  { 13.13, 14.14, 15.15, 16.16 }
	}};


	constexpr const Mat4 b {{
	  { 17.17, 18.18, 19.19, 20.20 },
	  { 21.21, 22.22, 23.23, 24.24 },
	  { 25.25, 26.26, 27.27, 28.28 },
	  { 29.29, 30.30, 31.31, 32.32 }
	}};


	const Mat4 add = a + b;
	const Mat4 sub = a - b;
	const Mat4 mul = a * b;

	print("A:", a);
	print("\n\nB:", b);
	print("\n\nADD:", add);
	print("\n\nSUB:", sub);
	print("\n\nMUL:", mul);
	return 0;
}
















