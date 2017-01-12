#include <stdio.h>
#include "renderer.hpp"
#include "finally.hpp"

namespace gp {

static GLuint vao_id = 0;
static GLuint vbo_id = 0;
static GLuint ebo_id = 0;

static void fill_vbo(const Vertex* const vertices, const long count);


bool initialize_renderer()
{
	auto failure_guard = finally([] {
		terminate_renderer();
	});

	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);
	glGenBuffers(1, &vbo_id);
	glGenBuffers(1, &ebo_id);
	glBindVertexArray(0);

	if (!vao_id || !vbo_id || !ebo_id) {
		fprintf(stderr, "%s\n", glewGetErrorString(glGetError()));
		return false;
	}

	failure_guard.Abort();
	return true;
}


void terminate_renderer()
{
	glBindVertexArray(vao_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo_id);
	glDeleteBuffers(1, &ebo_id);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao_id);
	ebo_id = 0;
	vao_id = 0;
	vbo_id = 0;
}


void draw_elements(const GLenum mode, const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices)
{
	const auto ind_count = indices.size();
	glBindVertexArray(vao_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

	fill_vbo(vertices.data(), vertices.size());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * ind_count, indices.data(), GL_STREAM_DRAW);
	glDrawElements(mode, ind_count, GL_UNSIGNED_INT, static_cast<GLvoid*>(0));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}


void draw_arrays(const GLenum mode, const std::vector<Vertex>& vertices)
{
	const auto ver_count = vertices.size();
	glBindVertexArray(vao_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

	fill_vbo(vertices.data(), ver_count);

	glDrawArrays(mode, 0, ver_count);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void fill_vbo(const Vertex* const vertices, const long count)
{
	constexpr auto vertsize = sizeof(*vertices);
	const auto buffsize = vertsize * count;
	const auto pos_offset = (GLvoid*) offsetof(Vertex, pos);
	const auto tex_offset = (GLvoid*) offsetof(Vertex, tex);
	const auto col_offset = (GLvoid*) offsetof(Vertex, color);

	glBufferData(GL_ARRAY_BUFFER, buffsize, vertices, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, vertsize, pos_offset);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertsize, tex_offset);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, vertsize, col_offset);
	glEnableVertexAttribArray(2);
}


} // namespace gp
