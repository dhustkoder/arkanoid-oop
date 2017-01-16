#ifndef GPROJ_MATH_TYPES_HPP_
#define GPROJ_MATH_TYPES_HPP_

namespace gp {

	
constexpr const float kPI = 3.14159265359f;


struct Vec2 {
	union { float x, r, s; };
	union { float y, g, t; };	
};


struct Vec3 {
	union { float x, r, s; };
	union { float y, g, t; };
	union { float z, b, p; };
};


struct Vec4 {
	union { float x, r, s; };
	union { float y, g, t; };
	union { float z, b, p; };
	union { float w, a, q; };
};


struct Mat4 {
	float data[4][4];
	const float (&operator[](int index) const)[4];
	float (&operator[](int index))[4];
};


} // namespace gp
#endif

