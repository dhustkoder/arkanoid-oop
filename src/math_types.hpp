#ifndef GPROJ_MATH_TYPES_HPP_
#define GPROJ_MATH_TYPES_HPP_
#include <GL/gl.h>

namespace gp {

struct Vec2 {
	union { GLfloat x, r, s; };
	union { GLfloat y, g, t; };
};


struct Vec3 {
	union { GLfloat x, r, s; };
	union { GLfloat y, g, t; };
	union { GLfloat z, b, p; };
};


struct Vec4 {
	union { GLfloat x, r, s; };
	union { GLfloat y, g, t; };
	union { GLfloat z, b, p; };
	union { GLfloat w, a, q; };
};


struct Mat4 {
	Vec4 x, y, z, t;
};



}
#endif

