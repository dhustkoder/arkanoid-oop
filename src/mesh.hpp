#ifndef GPROJ_MESH_HPP_
#define GPROJ_MESH_HPP_
#include <GL/glew.h>
#include <glm/vec4.hpp>

namespace gp {

struct Vertex {
	glm::vec4 pos;
	glm::vec4 color;
};

struct Mesh {
	long vertices_count;
	GLenum mode;
	GLuint vao_id;
	GLuint vbo_id;
};


extern Mesh* create_mesh(GLenum mode, const Vertex vertices[], long vertices_count);

extern void destroy_mesh(Mesh* mesh);

inline void bind_mesh(const Mesh& mesh)
{
	glBindVertexArray(mesh.vao_id);
}

inline void draw_mesh(const Mesh& mesh)
{
	glDrawArrays(mesh.mode, 0, mesh.vertices_count);
}


} // namespace gp
#endif

