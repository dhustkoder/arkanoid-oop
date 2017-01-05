#include <stdio.h>
#include <GL/glew.h>
#include "renderer.hpp"

namespace gp {

static GLuint vao_id = 0;
static GLuint vbo_id = 0;
static GLuint ebo_id = 0;

bool initialize_renderer()
{

	glGenVertexArrays(1, &vao_id);
	if (vao_id == 0) {
		fprintf(stderr, "%s\n", glewGetErrorString(glGetError()));
		return false;
	}

	glBindVertexArray(vao_id);
	glGenBuffers(1, &vbo_id);
	glGenBuffers(1, &ebo_id);
	return true;
}


void terminate_renderer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo_id);
	glDeleteBuffers(1, &ebo_id);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao_id);
	ebo_id = 0;
	vao_id = 0;
	vbo_id = 0;
}


void draw_elements(const GLenum mode, const std::vector<Vec3f>& vertices, const std::vector<GLuint>& indices)
{
	const auto ver_count = vertices.size();
	const auto ind_count = indices.size();
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f) * ver_count, vertices.data(), GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3f), static_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * ind_count, indices.data(), GL_STREAM_DRAW);
	glDrawElements(mode, ind_count, GL_UNSIGNED_INT, static_cast<GLvoid*>(0));

}

void draw_arrays(const GLenum mode, const std::vector<Vec3f>& vertices)
{
	const auto ver_count = vertices.size();
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f) * ver_count, vertices.data(), GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3f), static_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);
	glDrawArrays(mode, 0, ver_count);
}



}