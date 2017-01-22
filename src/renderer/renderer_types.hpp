#ifndef GPROJ_RENDER_TYPES_HPP_
#define GPROJ_RENDER_TYPES_HPP_
#include "math/math_types.hpp"

namespace gp {

constexpr const int kMaxTextures = 1;
constexpr const int kMaxShaders = 1;
constexpr const int kErrorMsgBufferSize = 1024;


struct Vertex {
	Vec3 pos;
	Vec2 tex;
	Vec4 color;
};


struct Indices {
	const unsigned int* data;
	int count;
};


struct Vertices {
	const Vertex* data;
	int count;
};


struct Elements {
	Vertices vertices;
	Indices indices;
};


struct ShadersProgramsFiles {
	const char* const* const vertex;
	const char* const* const fragment;
	const int count;
};


struct TexturesFiles {
	const char* const* const files;
	const int count;
};


struct ShaderLocs {
	int projection, view, model, light_color;
};

struct ShaderIds {
	unsigned int vertex, fragment;
};


} // namespace gp
#endif

