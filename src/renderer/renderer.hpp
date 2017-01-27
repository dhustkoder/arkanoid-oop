#ifndef GPROJ_RENDERER_HPP_
#define GPROJ_RENDERER_HPP_
#include <assert.h>
#include <GL/glew.h>
#include "memory/array.hpp"
#include "renderer_types.hpp"

namespace gp {

extern bool initialize_renderer(const char* title,
                                int width,
				int height,
                                const TexturesFiles& textures,
				const ShadersProgramsFiles& shaders);

extern void terminate_renderer();



inline void set_wireframe_mode(const bool on)
{
	glPolygonMode(GL_FRONT_AND_BACK, on ? GL_LINE : GL_FILL);
}


inline void clear_screen(const Vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


inline int register_vertex_buffer(const Vertices& vertices)
{
	extern Array<const Vertices*> vertexbuffers;
	const int offset = vertexbuffers.size;
	push_back(&vertices, &vertexbuffers);
	return offset;
}


inline int register_element_buffer(const Elements& elements)
{
	extern Array<const Elements*> elementbuffers;
	const int offset = elementbuffers.size;
	push_back(&elements, &elementbuffers);
	return offset;
}


inline void bind_vertex_buffer(const int offset)
{
	extern GLuint vao_id;
	extern GLuint vbo_id;
	extern Array<const Vertices*> vertexbuffers;
	extern const Vertices* bound_vertex_buffer;
	extern void fill_vbo(const Vertex* vertices, const int count);

	bound_vertex_buffer = vertexbuffers[offset];
	glBindVertexArray(vao_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	fill_vbo(bound_vertex_buffer->data, bound_vertex_buffer->count);
}


inline void bind_element_buffer(const int offset)
{
	extern GLuint vao_id;
	extern GLuint vbo_id;
	extern GLuint ebo_id;
	extern Array<const Elements*> elementbuffers;
	extern const Elements* bound_element_buffer;
	extern void fill_vbo(const Vertex* vertices, const int count);

	bound_element_buffer = elementbuffers[offset];
	const Vertices& vertices = bound_element_buffer->vertices;
	const Indices& indices = bound_element_buffer->indices;
	const GLsizei ind_count = bound_element_buffer->indices.count;

	glBindVertexArray(vao_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

	fill_vbo(vertices.data, vertices.count);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*indices.data) * ind_count, indices.data, GL_STREAM_DRAW);
}


inline void draw_vertex_buffer(const GLenum mode)
{
	extern const Vertices* bound_vertex_buffer;
	glDrawArrays(mode, 0, bound_vertex_buffer->count);
}


inline void draw_element_buffer(const GLenum mode)
{
	extern const Elements* bound_element_buffer;
	glDrawElements(mode, bound_element_buffer->indices.count, GL_UNSIGNED_INT, 0);
}


inline void unbind_vertex_buffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


inline void unbind_element_buffers()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


} // namespace gp
#endif
