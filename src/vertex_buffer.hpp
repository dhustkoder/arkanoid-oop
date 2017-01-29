#ifndef GPROJ_VERTEX_BUFFER_HPP_
#define GPROJ_VERTEX_BUFFER_HPP_
#include <GL/glew.h>


namespace gp {


class VertexBuffer {
public:
	VertexBuffer(const VertexBuffer& other) = delete;
	VertexBuffer& operator=(const VertexBuffer& other) = delete;

	VertexBuffer(GLfloat* data, GLsizei count, GLuint componentCount) noexcept;
	VertexBuffer(VertexBuffer&& other) noexcept;
	~VertexBuffer();

	void enable() const;
	void disable() const;
	GLuint getComponenetCount() const;

	VertexBuffer& operator=(VertexBuffer&& other) noexcept;
private:
	GLuint m_bufferId;
	GLuint m_componentCount;
};


inline void VertexBuffer::enable() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
}


inline void VertexBuffer::disable() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


inline GLuint VertexBuffer::getComponenetCount() const
{
	return m_componentCount;
}


} // namespace gp
#endif

