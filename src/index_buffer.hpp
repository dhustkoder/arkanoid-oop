#ifndef GPROJ_INDEX_BUFFER_HPP_
#define GPROJ_INDEX_BUFFER_HPP_
#include <GL/glew.h>


namespace gp {


class IndexBuffer {
public:
	IndexBuffer(const IndexBuffer& other) = delete;
	IndexBuffer& operator=(const IndexBuffer& other) = delete;

	IndexBuffer() = default;
	IndexBuffer(const GLushort* data, GLsizei count) noexcept;
	IndexBuffer(IndexBuffer&& other) noexcept;
	~IndexBuffer();

	void enable() const;
	void disable() const;
	GLuint getCount() const;

	IndexBuffer& operator=(IndexBuffer&& other) noexcept;
private:
	GLuint m_bufferId = 0;
	GLuint m_count = 0;
};


inline void IndexBuffer::enable() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
}


inline void IndexBuffer::disable() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


inline GLuint IndexBuffer::getCount() const
{
	return m_count;
}


} // namespace gp
#endif

