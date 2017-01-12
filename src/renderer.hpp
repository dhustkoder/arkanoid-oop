#ifndef GPROJ_RENDERER_HPP_
#define GPROJ_RENDERER_HPP_
#include <vector>
#include <GL/gl.h>
#include "math_types.hpp"

namespace gp {


struct Vertex {
	Vec2 pos;
	Vec2 tex;
	Vec4 color;
};


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
