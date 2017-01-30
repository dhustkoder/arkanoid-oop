#include "index_buffer.hpp"


namespace gp {

	
IndexBuffer::IndexBuffer(const GLushort* const data, const GLsizei count) noexcept
	: m_count(count)
{
	glGenBuffers(1, &m_bufferId);
	enable();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
	disable();
}


IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
	: m_bufferId(other.m_bufferId),
	m_count(other.m_count)
{
	other.m_bufferId = 0;
	other.m_count = 0;
}


IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_bufferId);
}


IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
	if (this != &other) {
		const GLuint aux_id = m_bufferId;
		const GLuint aux_count = m_count;
		m_bufferId = other.m_bufferId;
		m_count = other.m_count;
		other.m_bufferId = aux_id;
		other.m_count = aux_count;
	}

	return *this;
}


} // namespace gp

