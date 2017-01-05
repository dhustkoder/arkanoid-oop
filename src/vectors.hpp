#ifndef GPROJ_VECTORS_HPP_
#define GPROJ_VECTORS_HPP_
#include <stdint.h>
#include <GL/gl.h>

namespace gp {

template<class T>
struct Vector2 {
	union { T x, r, s; };
	union { T y, g, t; };
};

template<class T>
struct Vector3 {
	union { T x, r, s; };
	union { T y, g, t; };
	union { T z, b, p; };
};

template<class T>
struct Vector4 {
	union { T x, r, s; };
	union { T y, g, t; };
	union { T z, b, p; };
	union { T w, a, q; };
};

using Vec2f = Vector2<GLfloat>;
using Vec3f = Vector3<GLfloat>;
using Vec4f = Vector4<GLfloat>;

using Vec2i = Vector2<int_fast32_t>;
using Vec3i = Vector3<int_fast32_t>;
using Vec4i = Vector4<int_fast32_t>;

}
#endif

