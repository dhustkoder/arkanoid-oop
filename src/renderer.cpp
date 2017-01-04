#include <stdio.h>
#include <GL/glew.h>
#include "renderer.hpp"

namespace gp {

static GLuint vao_id = 0;
static GLuint vbo_id = 0;
static GLuint ebo_id = 0;

static void fill_vbo(const Vertex* const vertices, const long count);

bool initialize_renderer()
{

	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);
	glGenBuffers(1, &vbo_id);
	glGenBuffers(1, &ebo_id);
	glBindVertexArray(0);

	if (!vao_id || !vbo_id || !ebo_id) {
		fprintf(stderr, "%s\n", glewGetErrorString(glGetError()));
		terminate_renderer();
		return false;
	}

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices) * count, vertices, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(*vertices), (GLvoid*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(*vertices), (GLvoid*)(offsetof(Vertex, color)));
	glEnableVertexAttribArray(1);
}


}
