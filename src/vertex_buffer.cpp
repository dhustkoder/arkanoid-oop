#include "vertex_buffer.hpp"


namespace gp {

	
VertexBuffer::VertexBuffer(const GLsizei buffer_size) noexcept
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	enable();
	glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_DYNAMIC_DRAW);
	disable();
}


VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
	: m_vao(other.m_vao),
	m_vbo(other.m_vbo)
{
	other.m_vao = 0;
	other.m_vbo = 0;
}


VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}


void VertexBuffer::registerAttribArray(const GLuint index,
                                       const GLint components,
                                       const GLsizei stride,
                                       const std::uintptr_t offset) noexcept
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, components, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
}


VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
	if (this != &other) {
		const GLuint aux_vao = m_vao;
		const GLuint aux_vbo = m_vbo;
		m_vao = other.m_vao;
		m_vbo = other.m_vbo;
		other.m_vao = aux_vao;
		other.m_vbo = aux_vbo;
	}

	return *this;
}


} // namespace gp

