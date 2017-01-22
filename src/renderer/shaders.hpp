#ifndef GPROJ_SHADERS_HPP_
#define GPROJ_SHADERS_HPP_
#include <assert.h>
#include <GL/glew.h>
#include "renderer_types.hpp"

namespace gp {

inline void bind_shader(const int program_index)
{
	extern GLuint programs_ids[kMaxShaders];
	assert(program_index < kMaxShaders);
	glUseProgram(programs_ids[program_index]);
}


inline void unbind_shaders()
{
	glUseProgram(0);
}


inline void set_shader_projection(const int program, const Mat4& mat4)
{
	extern ShaderLocs shaders_locs[kMaxShaders];
	glUniformMatrix4fv(shaders_locs[program].projection, 1, GL_FALSE, &mat4[0][0]);
}


inline void set_shader_view(const int program, const Mat4& mat4)
{
	extern ShaderLocs shaders_locs[kMaxShaders];
	glUniformMatrix4fv(shaders_locs[program].view, 1, GL_FALSE, &mat4[0][0]);
}


inline void set_shader_model(const int program, const Mat4& mat4)
{
	extern ShaderLocs shaders_locs[kMaxShaders];
	glUniformMatrix4fv(shaders_locs[program].model, 1, GL_FALSE, &mat4[0][0]);
}


inline void set_shader_light_color(const int program, const Vec3& vec3)
{
	extern ShaderLocs shaders_locs[kMaxShaders];
	glUniform3f(shaders_locs[program].light_color, vec3.r, vec3.g, vec3.b);
}


}
#endif
