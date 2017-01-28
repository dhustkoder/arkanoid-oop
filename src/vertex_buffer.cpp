#include "vertex_buffer.hpp"


namespace gp {

	
VertexBuffer::VertexBuffer(GLfloat* const data, const GLsizei count, const GLuint componentCount) noexcept
	: m_componentCount(componentCount)
{
	glGenBuffers(1, &m_bufferId);
	enable();
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
	disable();
}


VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
	: m_bufferId(other.m_bufferId),
	m_componentCount(other.m_componentCount)
{
	other.m_bufferId = 0;
	other.m_componentCount = 0;
}


VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_bufferId);
}


VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
	if (this != &other) {
		const GLuint aux_id = m_bufferId;
		const GLuint aux_count = m_componentCount;
		m_bufferId = other.m_bufferId;
		m_componentCount = other.m_componentCount;
		other.m_bufferId = aux_id;
		other.m_componentCount = aux_count;
	}

	return *this;
}


} // namespace gp

