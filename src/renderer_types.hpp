#ifndef GPROJ_RENDER_TYPES_HPP_
#define GPROJ_RENDER_TYPES_HPP_
#include "math_types.hpp"

namespace gp {


struct Vertex {
	Vec2 pos;
	Vec2 tex;
	Vec4 color;
};


struct Indices {
	const unsigned int* const data;
	const long count;
};

struct Vertices {
	const Vertex* const data;
	const long count;
};


struct Elements {
	const Vertices vertices;
	const Indices indices;
};



} // namespace gp
#endif

