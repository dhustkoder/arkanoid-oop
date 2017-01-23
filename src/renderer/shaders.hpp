#ifndef GPROJ_SHADERS_HPP_
#define GPROJ_SHADERS_HPP_
#include <assert.h>
#include <GL/glew.h>
#include "renderer_types.hpp"

namespace gp {

inline void bind_shader(const int program_index)
{
	extern GLuint programs_ids[kMaxShaders];
	extern GLuint bound_shader_id;
	extern int bound_shader_index;
	bound_shader_id = programs_ids[program_index];
	bound_shader_index = program_index;
	glUseProgram(bound_shader_id);
}


inline void unbind_shaders()
{
	glUseProgram(0);
}


inline void set_shader_projection(const Mat4& mat4)
{
	extern ShaderLocs shaders_locs[kMaxShaders];
	extern int bound_shader_index;
	glUniformMatrix4fv(shaders_locs[bound_shader_index].projection, 1, GL_FALSE, &mat4[0][0]);
}


inline void set_shader_view(const Mat4& mat4)
{
	extern ShaderLocs shaders_locs[kMaxShaders];
	extern int bound_shader_index;
	glUniformMatrix4fv(shaders_locs[bound_shader_index].view, 1, GL_FALSE, &mat4[0][0]);
}


inline void set_shader_model(const Mat4& mat4)
{
	extern ShaderLocs shaders_locs[kMaxShaders];
	extern int bound_shader_index;
	glUniformMatrix4fv(shaders_locs[bound_shader_index].model, 1, GL_FALSE, &mat4[0][0]);
}


inline void set_shader_light_pos(const Vec3& v)
{
	extern ShaderLocs shaders_locs[kMaxShaders];
	extern int bound_shader_index;
	glUniform3f(shaders_locs[bound_shader_index].light_pos, v.x, v.y, v.z);
}


inline void set_shader_view_pos(const Vec3& v)
{
	extern ShaderLocs shaders_locs[kMaxShaders];
	extern int bound_shader_index;
	glUniform3f(shaders_locs[bound_shader_index].view_pos, v.x, v.y, v.z);
}


inline void set_shader_light_color(const Vec3& v)
{
	extern ShaderLocs shaders_locs[kMaxShaders];
	extern int bound_shader_index;
	glUniform3f(shaders_locs[bound_shader_index].light_color, v.r, v.g, v.b);
}


inline void set_shader_object_color(const Vec3& v)
{
	extern ShaderLocs shaders_locs[kMaxShaders];
	extern int bound_shader_index;
	glUniform3f(shaders_locs[bound_shader_index].object_color, v.r, v.g, v.b);
}


}
#endif
