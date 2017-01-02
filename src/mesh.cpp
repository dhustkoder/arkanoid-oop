#include <stdlib.h>
#include <stdio.h>
#include "mesh.hpp"
#include "finally.hpp"

namespace gp {

Mesh* create_mesh(const GLenum mode,
                  const Vertex* vertices,
                  const long vertices_count,
                  const long buffers_count)
{
	Mesh* const mesh = 
	  static_cast<Mesh*>(malloc(sizeof(Mesh) + sizeof(GLuint) * buffers_count));
	
	if (mesh == nullptr) {
		perror("");
		return nullptr;
	}

	auto mesh_guard = finally([mesh] {
		destroy_mesh(mesh);
	});

	mesh->buffers_count = buffers_count;
	mesh->vertices_count = vertices_count;
	mesh->mode = mode;

	GLenum error = glGetError();

	glGenVertexArrays(1, &mesh->vao_id);
	glBindVertexArray(mesh->vao_id);
	glGenBuffers(buffers_count, &mesh->buffers_ids[0]);

	const auto vertex_size = sizeof(Vertex);
	const auto buffer_size = sizeof(Vertex) * vertices_count;
	const auto color_offset = reinterpret_cast<GLvoid*>(sizeof(Vertex::pos));

	for (long i = 0; i < buffers_count; ++i) {
		glBindBuffer(GL_ARRAY_BUFFER, mesh->buffers_ids[i]);
		glBufferData(GL_ARRAY_BUFFER, buffer_size, &vertices[i * vertices_count], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, vertex_size, nullptr);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertex_size, color_offset);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
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




