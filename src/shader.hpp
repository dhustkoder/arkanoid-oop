#ifndef GPROJ_SHADER_HPP_
#define GPROJ_SHADER_HPP_
#include <string>
#include "vectors.hpp"

namespace gp {

extern bool initialize_shader();
extern void terminate_shader();
extern void set_shader_uniform(const std::string& name, const Vec4f& value);


} // namespace gp
#endif
