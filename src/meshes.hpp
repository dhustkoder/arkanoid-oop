#ifndef GPROJ_MESHES_HPP_
#define GPROJ_MESHES_HPP_
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace gp {

using Vertex = glm::vec4[3];
using Color = glm::vec4[3];

struct Meshes {
	GLuint vao_id;
	GLuint vbo_id;
	GLuint cbo_id;
	long count;
};

extern bool load_meshes(const Vertex* vertices, const Color* colors,
                        long count, Meshes* meshes);
extern void release_meshes(Meshes* meshes);

inline void draw_meshes(const Meshes& meshes)
{
	glBindVertexArray(meshes.vao_id);
	glDrawArrays(GL_TRIANGLES, 0, meshes.count);
	glBindVertexArray(0);
}


} // namespace gp
#endif

