#include <stdio.h>
#include <string.h>
#include "meshes.hpp"

namespace gp {

Meshes* create_meshes(Vertex* const data, const long height, const long width)
{
	const auto data_size = sizeof(Vertex) * height * width;
	Meshes* const meshes =
		static_cast<Meshes*>(malloc(sizeof(Meshes) + data_size));
		
	if (meshes == nullptr) {
		perror("");
		return nullptr;
	}

	meshes->height = height;
	meshes->width = width;
	memcpy(&meshes->data[0], &data[0], data_size);

	glGenVertexArrays(1, &meshes->vertex_array_obj);
	glBindVertexArray(meshes->vertex_array_obj);
	glGenBuffers(kVertexBuffersSize, meshes->vertex_array_buffers);
	glBindBuffer(GL_ARRAY_BUFFER,
	             meshes->vertex_array_buffers[kVertexBufferPosition]);
	glBufferData(GL_ARRAY_BUFFER, data_size, meshes->data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);


	return meshes;
}

void destroy_meshes(Meshes* const meshes)
{
	glDeleteVertexArrays(1, &meshes->vertex_array_obj);
	free(meshes);
}

void draw_meshes(const Meshes& meshes)
{
	glBindVertexArray(meshes.vertex_array_obj);
	glDrawArrays(GL_TRIANGLES, 0, meshes.height * meshes.width);
	glBindVertexArray(0);
}


} // namespace gp

