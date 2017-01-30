#ifndef GPROJ_VERTEX_BUFFER_HPP_
#define GPROJ_VERTEX_BUFFER_HPP_
#include <cstdint>
#include <GL/glew.h>
#include "vertex_data.hpp"

namespace gp {



class VertexBuffer {
public:
	VertexBuffer(const VertexBuffer& other) = delete;
	VertexBuffer& operator=(const VertexBuffer& other) = delete;
	VertexBuffer(GLsizei buffer_size) noexcept;
	VertexBuffer(VertexBuffer&& other) noexcept;
	~VertexBuffer();

	void enable() const;
	void disable() const;
	void registerAttribArray(GLuint index, GLint components, GLsizei stride, std::uintptr_t offset) noexcept;

	VertexData* mapWriteOnlyBuffer()
	{
		enable();
		return reinterpret_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	}

	void unmapWriteOnlyBuffer()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		disable();
	}


	VertexBuffer& operator=(VertexBuffer&& other) noexcept;
private:
	GLuint m_vao;
	GLuint m_vbo;
};


inline void VertexBuffer::enable() const
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}


inline void VertexBuffer::disable() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


} // namespace gp
#endif

