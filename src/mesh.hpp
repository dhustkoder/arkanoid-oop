#ifndef GPROJ_MESH_HPP_
#define GPROJ_MESH_HPP_
#include <GL/glew.h>
#include <glm/vec4.hpp>

namespace gp {

struct Vertex {
	glm::vec4 x, y, z;
};

struct Mesh {
	long vertices_count;
	long buffers_count;
	GLuint vao_id;
	GLuint buffers_ids[];
};


extern Mesh* create_mesh(const Vertex* const* vertices,
                         const long vertices_arrays_size,
			 const long count);

extern void destroy_mesh(Mesh* mesh);

inline void draw_mesh(const Mesh& mesh)
{
	glBindVertexArray(mesh.vao_id);
	glDrawArrays(GL_TRIANGLES, 0, mesh.vertices_count);
}


} // namespace gp
#endif

