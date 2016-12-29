#ifndef GPROJ_MESHES_HPP_
#define GPROJ_MESHES_HPP_
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace gp {

using Vertex = glm::vec3;

enum VertexBuffers {
	kVertexBufferPosition,
	kVertexBuffersSize
};

struct Meshes {
	GLuint vertex_array_obj;
	GLuint vertex_array_buffers[kVertexBuffersSize];
	long height;
	long width;
	Vertex data[];
};

extern Meshes* create_meshes(Vertex* data, long height, long width);
extern void destroy_meshes(Meshes* meshes);
extern void draw_meshes(const Meshes& meshes);


} // namespace gp
#endif

