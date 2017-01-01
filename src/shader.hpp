#ifndef GPROJ_SHADER_HPP_
#define GPROJ_SHADER_HPP_
#include <GL/glew.h>

namespace gp {

struct Shader {
	GLuint id;
	long count;
	GLuint shaders[];
};

extern Shader* create_shader(const char* const* filepaths,
                             const GLenum* types,
                             long count);

extern void destroy_shader(Shader* program);

inline void bind_shader(const Shader& program)
{
	glUseProgram(program.id);
}


} // namespace gp
#endif
