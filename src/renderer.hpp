#ifndef GPROJ_RENDERER_HPP_
#define GPROJ_RENDERER_HPP_
#include <vector>
#include <string>
#include <GL/glew.h>
#include "renderer_types.hpp"

namespace gp {

extern bool initialize_renderer(const std::vector<std::string>& textures_files,
                                const std::vector<std::pair<std::string, std::string>>& shaders_programs);

extern void terminate_renderer();


extern void draw(GLenum mode, const Elements& elements);
extern void draw(GLenum mode, const Vertices& vertices);
extern void set_uniform(const long program, const Mat4& mat4, const char* name);


inline void set_wireframe_mode(const bool on)
{
	glPolygonMode(GL_FRONT_AND_BACK, on ? GL_LINE : GL_FILL);
}


inline void bind_texture(const long index)
{
	extern std::vector<GLuint> textures_ids;
	glBindTexture(GL_TEXTURE_2D, textures_ids[index]);
}


inline void unbind_texture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


inline void bind_shader(const long program_index)
{
	extern std::vector<GLuint> programs_ids;
	glUseProgram(programs_ids[program_index]);
}


inline void unbind_shader()
{
	glUseProgram(0);
}


} // namespace gp
#endif

