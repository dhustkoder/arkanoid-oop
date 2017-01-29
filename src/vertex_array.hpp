#ifndef GPROJ_VERTEX_ARRAY_HPP_
#define GPROJ_VERTEX_ARRAY_HPP_
#include <vector>
#include "vertex_buffer.hpp"

namespace gp {


class VertexArray {
public:
	VertexArray(const VertexArray&) = delete;
	VertexArray(VertexArray&&) = delete;

	VertexArray() noexcept;
	~VertexArray();

	void enable() const;
	void disable() const;

	void addBuffer(VertexBuffer&& buffer, GLuint index);
	void addBuffer(GLfloat* data, GLsizei count, GLuint componentCount, GLuint index);

private:
	std::vector<VertexBuffer> m_buffers;
	GLuint m_arrayId;
};


inline void VertexArray::enable() const
{
	glBindVertexArray(m_arrayId);
}


inline void VertexArray::disable() const
{
	glBindVertexArray(0);
}


inline void VertexArray::addBuffer(GLfloat* const data,
                            const GLsizei count,
                            const GLuint componentCount,
                            const GLuint index)
{
	addBuffer(VertexBuffer(data, count, componentCount), index);
}


} // namespace gp
#endif

