#ifndef GPROJ_RENDERER_HPP_
#define GPROJ_RENDERER_HPP_
#include <assert.h>
#include <GL/glew.h>
#include "renderer_types.hpp"


namespace gp {

extern bool initialize_renderer(const TexturesFiles& textures, const ShadersProgramsFiles& shaders);
extern void terminate_renderer();

extern void draw(GLenum mode, const Elements& elements);
extern void draw(GLenum mode, const Vertices& vertices);
extern void set_uniform(const int program, const Mat4& mat4, const char* name);


inline void set_wireframe_mode(const bool on)
{
	glPolygonMode(GL_FRONT_AND_BACK, on ? GL_LINE : GL_FILL);
}


inline void bind_texture(const int index)
{
	extern GLuint textures_ids[kMaxTextures];
	assert(index < kMaxTextures);
	glBindTexture(GL_TEXTURE_2D, textures_ids[index]);
}


inline void unbind_textures()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


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


} // namespace gp
#endif

