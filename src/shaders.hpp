#ifndef GPROJ_SHADERS_HPP_
#define GPROJ_SHADERS_HPP_
#include <GL/glew.h>

namespace gp {

struct Shaders {
	GLuint program;
	long size;
	GLuint ids[];
};

extern Shaders* create_shaders();
extern void destroy_shaders(Shaders* shaders);

inline void bind_shaders(const Shaders& shaders)
{
	glUseProgram(shaders.program);
}


} // namespace gp
#endif
