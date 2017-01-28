#ifndef GPROJ_VERTEX_ARRAY_HPP_
#define GPROJ_VERTEX_ARRAY_HPP_
#include <vector>
#include "vertex_buffer.hpp"

namespace gp {

class VertexArray {
public:
	VertexArray();
	~VertexArray();
private:
	std::vector<VertexBuffer> m_vertexBuffers;
};


} // namespace gp

#endif

