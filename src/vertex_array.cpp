#include "vertex_array.hpp"


namespace gp {

	
VertexArray::VertexArray() noexcept
{
	glGenVertexArrays(1, &m_arrayId);
}


VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_arrayId);
}


void VertexArray::addBuffer(VertexBuffer&& buffer, const GLuint index)
{
	enable();
	buffer.enable();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer.getComponenetCount(), GL_FLOAT, GL_FALSE, 0, 0);

	buffer.disable();
	disable();

	m_buffers.emplace_back(std::move(buffer));
}


} // namespace gp

