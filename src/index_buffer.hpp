#ifndef GPROJ_INDEX_BUFFER_HPP_
#define GPROJ_INDEX_BUFFER_HPP_
#include <GL/glew.h>


namespace gp {


class IndexBuffer {
public:
	IndexBuffer(const IndexBuffer& other) = delete;
	IndexBuffer& operator=(const IndexBuffer& other) = delete;

	IndexBuffer(GLushort* data, GLsizei count, GLuint componentCount) noexcept;
	IndexBuffer(IndexBuffer&& other) noexcept;
	~IndexBuffer();

	void enable() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId); }
	void disable() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	IndexBuffer& operator=(IndexBuffer&& other) noexcept;
	
private:
	GLuint m_bufferId;
	GLuint m_componentCount;
};


} // namespace gp
#endif

