#include <stdlib.h>
#include <stdio.h>
#include "mesh.hpp"
#include "finally.hpp"

namespace gp {

Mesh* create_mesh(const GLenum mode,
                  const Vertex* const* vertices,
                  const long vertices_arrays_count,
                  const long count)
{
	Mesh* const mesh =
	  static_cast<Mesh*>(malloc(sizeof(Mesh) + sizeof(GLuint) * count));
	
	if (mesh == nullptr) {
		perror("");
		return nullptr;
	}

	auto mesh_guard = finally([mesh] {
		destroy_mesh(mesh);
	});

	mesh->buffers_count = count;
	mesh->vertices_count = vertices_arrays_count;
	mesh->mode = mode;

	GLenum error = glGetError();

	glGenVertexArrays(1, &mesh->vao_id);
	glBindVertexArray(mesh->vao_id);
	glGenBuffers(count, &mesh->buffers_ids[0]);

	for (long i = 0; i < count; ++i) {
		glBindBuffer(GL_ARRAY_BUFFER, mesh->buffers_ids[i]);
		glBufferData(GL_ARRAY_BUFFER,
		             sizeof(Vertex) * vertices_arrays_count,
			     vertices[i],
			     GL_STATIC_DRAW);
		glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(i);
	}

	if ((error = glGetError()) != GL_NO_ERROR) {
		fprintf(stderr, "Couldn't create mesh: %s\n",
		        glewGetErrorString(error));
		return nullptr;
	}

	mesh_guard.Abort();
	return mesh;
}

void destroy_mesh(Mesh* const mesh)
{
	GLenum error = glGetError();

	glBindVertexArray(mesh->vao_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	for (long i = mesh->buffers_count - 1; i >= 0; --i)
		glDisableVertexAttribArray(i);

	glDeleteBuffers(mesh->buffers_count, &mesh->buffers_ids[0]);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &mesh->vao_id);

	if ((error = glGetError()) != GL_NO_ERROR) {
		fprintf(stderr, "Couldn't destroy mesh: %s\n",
		        glewGetErrorString(error));
	}

	free(mesh);
}

} // namespace gp




