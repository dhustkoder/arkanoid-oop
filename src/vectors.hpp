#ifndef GPROJ_VECTORS_HPP_
#define GPROJ_VECTORS_HPP_
#include <stdint.h>
#include <GL/gl.h>

namespace gp {

template<class T>
struct Vector2 {
	T x, y;
};

template<class T>
struct Vector3 {
	T x, y, z;
};

template<class T>
struct Vector4 {
	T x, y, z, w;
};

using Vec2f = Vector2<GLfloat>;
using Vec3f = Vector3<GLfloat>;
using Vec4f = Vector4<GLfloat>;

using Vec2i = Vector2<int_fast32_t>;
using Vec3i = Vector3<int_fast32_t>;
using Vec4i = Vector4<int_fast32_t>;

}
#endif

