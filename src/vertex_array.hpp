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

private:
	std::vector<VertexBuffer> m_buffers;
	GLuint m_arrayId;
};


} // namespace gp

#endif

