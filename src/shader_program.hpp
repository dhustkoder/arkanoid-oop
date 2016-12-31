#ifndef GPROJ_SHADER_PROGRAM_HPP_
#define GPROJ_SHADER_PROGRAM_HPP_
#include <GL/glew.h>

namespace gp {

struct ShaderProgram {
	GLuint id;
	long count;
	GLuint shaders[];
};

extern ShaderProgram* create_shader_program(const char* const* filepaths,
                                            const GLenum* types,
                                            long count);

extern void destroy_shader_program(ShaderProgram* program);

inline void bind_shader_program(const ShaderProgram& program)
{
	glUseProgram(program.id);
}


} // namespace gp
#endif
