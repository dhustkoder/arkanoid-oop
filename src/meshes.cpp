#include <stdio.h>
#include <string.h>
#include "meshes.hpp"

namespace gp {

bool load_meshes(const Vertex* const vertices,
                 const Color* const colors,
                 const long count,
                 Meshes* const meshes)
{
	const auto vertices_size = sizeof(*vertices) * count;
	const auto colors_size = sizeof(*colors) * count;
	meshes->count = vertices_size + colors_size;

	glGenVertexArrays(1, &meshes->vao_id);
	glBindVertexArray(meshes->vao_id);

	glGenBuffers(1, &meshes->vbo_id);
	glBindBuffer(GL_ARRAY_BUFFER, meshes->vbo_id);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &meshes->cbo_id);
	glBindBuffer(GL_ARRAY_BUFFER, meshes->cbo_id);
	glBufferData(GL_ARRAY_BUFFER, colors_size, colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	const auto error_check = glGetError();
	if (error_check != GL_NO_ERROR) {
		fprintf(stderr, "%s\n", glewGetErrorString(error_check));
		release_meshes(meshes);
		return false;
	}

	glBindVertexArray(0);

	return true;
}

void release_meshes(Meshes* const meshes)
{
	glDeleteVertexArrays(1, &meshes->vao_id);
}




} // namespace gp

