#include <stdio.h>
#include <GL/glew.h>
#include "renderer.hpp"

namespace gp {

static GLuint vao_id = 0;
static std::vector<GLuint> vbo_ids;

bool initialize_renderer()
{

	glGenVertexArrays(1, &vao_id);
	if (vao_id == 0) {
		fprintf(stderr, "%s\n", glewGetErrorString(glGetError()));
		return false;
	}

	glBindVertexArray(vao_id);
	return true;
}


void terminate_renderer()
{
	glBindVertexArray(0);
	
	if (vbo_ids.size() > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(vbo_ids.size(), vbo_ids.data());
	}

	glDeleteVertexArrays(1, &vao_id);
	vao_id = 0;
	vbo_ids.clear();
}


void draw_sprites()
{
	for (size_t i = 0; i < vbo_ids.size(); ++i) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[i]);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glDrawArrays(GL_QUADS, 0, 6);
	}
}


std::vector<GLuint> add_sprites(const Vec2* const positions,
                                const Vec2* const sizes,
                                const Color* const colors,
		                const bool* const dynamics,
		                const long count)
{
	const auto old_size = vbo_ids.size();
	vbo_ids.resize(old_size + count);
	glGenBuffers(count, &vbo_ids[old_size]);
	const GLuint* const new_ids = &vbo_ids[old_size];
	
	GLfloat buffer_data[12];

	for (long i = 0; i < count; ++i) {
		auto pos = positions[i];
		auto size = sizes[i];
		auto color = colors[i];
		auto dynamic = dynamics[i];
		auto id = new_ids[i];

		buffer_data[0] = pos.x;
		buffer_data[1] = pos.y;

		buffer_data[2] = pos.x + size.x;
		buffer_data[3] = pos.y;

		buffer_data[4] = pos.x + size.x;
		buffer_data[5] = pos.y - size.y;

		buffer_data[6] = pos.x;
		buffer_data[7] = pos.y - size.y;

		buffer_data[8] = color.r;
		buffer_data[9] = color.g;
		buffer_data[10] = color.b;
		buffer_data[11] = color.a;

		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data,
		             dynamic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	}

	return { vbo_ids.begin() + old_size, vbo_ids.end() };
}


}

