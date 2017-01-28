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

	void enable() const { glBindBuffer(GL_ARRAY_BUFFER, m_bufferId); }
	void disable() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	GLuint getComponenetCount() const { return m_componentCount; }

	VertexBuffer& operator=(VertexBuffer&& other) noexcept;
private:
	GLuint m_bufferId;
	GLuint m_componentCount;
};


} // namespace gp
#endif

