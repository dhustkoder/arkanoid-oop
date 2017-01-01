#ifndef GPROJ_VERTEX_HPP_
#define GPROJ_VERTEX_HPP_
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace gp {


struct Vertex {
	glm::vec4 x, y, z;
};

struct VertexArray {
	GLuint id;
	long count;
	long size;
	GLuint buffers_ids[];
};

extern VertexArray* create_vertex_array(const Vertex* vertices, long count);

extern void destroy_vertex_array(VertexArray* va);

inline void draw_vertex_array(VertexArray* const va)
{
	glBindVertexArray(va->id);
	glDrawArrays(GL_TRIANGLES, 0, va->size);
}


} // namespace gp
#endif

