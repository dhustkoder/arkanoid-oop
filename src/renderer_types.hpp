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
	unsigned int* data;
	long count;
};

struct Vertices {
	Vertex* data;
	long count;
};


struct Elements {
	Vertices vertices;
	Indices indices;
};



} // namespace gp
#endif

