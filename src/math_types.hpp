#ifndef ARKANOID_OOP_MATH_TYPES_HPP_
#define ARKANOID_OOP_MATH_TYPES_HPP_
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace gp {

using Vec2f = glm::vec2;
using Vec4f = glm::vec4;


inline std::ostream& operator<<(std::ostream& os, const Vec2f& v)
{
	os << "X " << v.x << " Y " << v.y;
	return os;
}


} // namespace gp
#endif

