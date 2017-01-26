#ifndef GPROJ_RENDER_TYPES_HPP_
#define GPROJ_RENDER_TYPES_HPP_
#include "math/math_types.hpp"

namespace gp {

constexpr const int kMaxTextures = 3;
constexpr const int kMaxShaders = 2;
constexpr const int kErrorMsgBufferSize = 1024;


struct Vertex {
	Vec3 pos;
	Vec2 tex_coords;
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
	int projection, 
	view, 
	model,
	light_pos,
	view_pos,
	light_color,
	object_color;
};


struct ShaderIds {
	unsigned int vertex, fragment;
};


struct Camera {
	float yaw;
	float pitch;
	float speed;
	float sensitivity;
	Vec3 pos;
	Vec3 dir;
	Vec3 right;
	Vec3 up;
	Vec3 world_up;
};


} // namespace gp
#endif


