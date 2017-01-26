#ifndef GPROJ_CAMERA_HPP_
#define GPROJ_CAMERA_HPP_
#include "math/math_types.hpp"

namespace gp {

extern void reset_camera(float speed, float sensitivity, const Vec3& pos, const Vec3& world_up);
extern void update_camera(float delta);


} // namespace gp
#endif

