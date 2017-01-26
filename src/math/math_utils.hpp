#ifndef GPROJ_MATH_UTILS_HPP_
#define GPROJ_MATH_UTILS_HPP_
#include "math_types.hpp"

namespace gp {

	
constexpr const float kPI = 3.14159265359f;


constexpr float radians(const float x)
{
	return x * (kPI / 180);
}


constexpr float degrees(const float x)
{
	return x * (180 / kPI);
}

	
template<class T>
constexpr T clamp(const T value, const T min, const T max)
{
	return value < min ? min : value > max ? max : value;
}


} // namespace gp
#endif

