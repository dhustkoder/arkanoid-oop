#include <stdlib.h>
#include <stdio.h>
#include "mesh.hpp"
#include "finally.hpp"

namespace gp {

Mesh* create_mesh(const GLenum mode, const Vertex vertices[], const long vertices_count)
{
	Mesh* const mesh = 
	  static_cast<Mesh*>(malloc(sizeof(Mesh) + sizeof(GLuint)));
	
	if (mesh == nullptr) {
		perror("");
		return nullptr;
	}

	auto mesh_guard = finally([mesh] {
		destroy_mesh(mesh);
	});

	mesh->vertices_count = vertices_count;
	mesh->mode = mode;

	GLenum error = glGetError();

	glGenVertexArrays(1, &mesh->vao_id);
	glBindVertexArray(mesh->vao_id);
	glGenBuffers(1, &mesh->vao_id);

	const auto buffer_size = sizeof(Vertex) * vertices_count;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vao_id);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

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

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &mesh->vbo_id);

	glBindVertexArray(0);

	glDeleteVertexArrays(1, &mesh->vao_id);

	if ((error = glGetError()) != GL_NO_ERROR) {
		fprintf(stderr, "Couldn't destroy mesh: %s\n",
		        glewGetErrorString(error));
	}

	free(mesh);
}

} // namespace gp




