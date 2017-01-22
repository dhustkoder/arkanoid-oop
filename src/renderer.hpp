#ifndef GPROJ_RENDERER_HPP_
#define GPROJ_RENDERER_HPP_
#include <assert.h>
#include <GL/glew.h>
#include "renderer_types.hpp"
#include "array.hpp"

namespace gp {

extern bool initialize_renderer(const TexturesFiles& textures, const ShadersProgramsFiles& shaders);
extern void terminate_renderer();


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


inline int register_vertex_buffer(const Vertices& vertices)
{
	extern Array<const Vertices*> vertexbuffers;
	const int offset = vertexbuffers.size;
	push(&vertices, &vertexbuffers);
	return offset;
}


inline int register_element_buffer(const Elements& elements)
{
	extern Array<const Elements*> elementbuffers;
	const int offset = elementbuffers.size;
	push(&elements, &elementbuffers);
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


inline void draw_element_buffer(const GLenum mode, const intptr_t from_offset, const intptr_t to_offset)
{
	extern const Elements* bound_element_buffer;
	glDrawElements(mode, to_offset - from_offset,
	              GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(sizeof(GLuint) * from_offset));
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


inline void set_shader_projection(const int program, const Mat4& mat4)
{
	extern ShaderLocs shaders_locs[kMaxShaders];
	glUniformMatrix4fv(shaders_locs[program].projection, 1, GL_FALSE, &mat4[0][0]);
}


inline void set_shader_view(const int program, const Mat4& mat4)
{
	extern ShaderLocs shaders_locs[kMaxShaders];
	glUniformMatrix4fv(shaders_locs[program].view, 1, GL_FALSE, &mat4[0][0]);
}


inline void set_shader_model(const int program, const Mat4& mat4)
{
	extern ShaderLocs shaders_locs[kMaxShaders];
	glUniformMatrix4fv(shaders_locs[program].model, 1, GL_FALSE, &mat4[0][0]);
}


inline void set_shader_light_color(const int program, const Vec3& vec3)
{
	extern ShaderLocs shaders_locs[kMaxShaders];
	glUniform3f(shaders_locs[program].light_color, vec3.r, vec3.g, vec3.b);
}


} // namespace gp
#endif

