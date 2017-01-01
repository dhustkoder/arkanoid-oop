#include <stdio.h>
#include <string.h>
#include "vertex.hpp"

namespace gp {

VertexArray* create_vertex_array(const Vertex* const vertices, const long count)
{
	const auto memsize = sizeof(VertexArray) + sizeof(GLuint) * count;
	VertexArray* const va = static_cast<VertexArray*>(malloc(memsize));

	if (va == nullptr) {
		perror("");
		return nullptr;
	}

	glGenVertexArrays(1, &va->id);
	glBindVertexArray(va->id);
	glGenBuffers(count, &va->buffers_ids[0]);
	va->count = count;
	va->size = sizeof(Vertex) * count;

	for (long i = 0; i < count; ++i) {
		glBindBuffer(GL_ARRAY_BUFFER, va->buffers_ids[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), &vertices[i], GL_STATIC_DRAW);
		glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(i);
	}

	return va;
}

void destroy_vertex_array(VertexArray* const va)
{
	glBindVertexArray(va->id);

	for (long i = va->count - 1; i >= 0; --i)
		glDisableVertexAttribArray(i);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(va->count, &va->buffers_ids[0]);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &va->id);
	free(va);
}


} // namespace gp

