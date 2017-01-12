#ifndef GPROJ_RENDERER_HPP_
#define GPROJ_RENDERER_HPP_
#include <vector>
#include <GL/glew.h>
#include "renderer_types.hpp"

namespace gp {

extern bool initialize_renderer();
extern void terminate_renderer();
extern void draw_elements(GLenum mode, const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
extern void draw_arrays(GLenum mode, const std::vector<Vertex>& vertices);

inline void set_wireframe_mode(const bool on)
{
	glPolygonMode(GL_FRONT_AND_BACK, on ? GL_LINE : GL_FILL);
}


} // namespace gp
#endif

