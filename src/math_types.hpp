#ifndef GPROJ_MATH_TYPES_HPP_
#define GPROJ_MATH_TYPES_HPP_

namespace gp {

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
	Vec4 x, y, z, t;
};



} // namespace gp
#endif

