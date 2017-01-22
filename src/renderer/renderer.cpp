#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <SOIL/SOIL.h>
#include "utils/finally.hpp"
#include "renderer.hpp"

namespace gp {


GLuint vao_id = 0;
GLuint vbo_id = 0;
GLuint ebo_id = 0;

Array<const Vertices*> vertexbuffers = make_array<const Vertices*>();
Array<const Elements*> elementbuffers = make_array<const Elements*>();
const Vertices* bound_vertex_buffer = nullptr;
const Elements* bound_element_buffer = nullptr;


static bool create_glbuffers();
static void free_glbuffers();


extern bool create_textures(const TexturesFiles& textures_files);
extern void free_textures();


extern bool create_shaders(const ShadersProgramsFiles& programs);
extern void free_shaders();


bool initialize_renderer(const TexturesFiles& textures, const ShadersProgramsFiles& shaders)
{
	auto failure_guard = finally([] {
		terminate_renderer();
	});

	if (!create_glbuffers() ||
	    !create_textures(textures) ||
	    !create_shaders(shaders))
		return false;

	failure_guard.Abort();
	return true;
}


void terminate_renderer()
{
	free_shaders();
	free_textures();
	free_glbuffers();
}




void fill_vbo(const Vertex* vertices, const int count)
{
	constexpr auto vertsize = sizeof(*vertices);
	const auto buffsize = vertsize * count;
	const auto pos_offset = (GLvoid*) offsetof(Vertex, pos);
	const auto tex_offset = (GLvoid*) offsetof(Vertex, tex);
	const auto col_offset = (GLvoid*) offsetof(Vertex, color);

	glBufferData(GL_ARRAY_BUFFER, buffsize, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, sizeof(Vertex::pos)/sizeof(GLfloat), GL_FLOAT, GL_FALSE, vertsize, pos_offset);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, sizeof(Vertex::tex)/sizeof(GLfloat), GL_FLOAT, GL_FALSE, vertsize, tex_offset);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, sizeof(Vertex::color)/sizeof(GLfloat), GL_FLOAT, GL_FALSE, vertsize, col_offset);
	glEnableVertexAttribArray(2);
}


bool create_glbuffers()
{
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);
	glGenBuffers(1, &vbo_id);
	glGenBuffers(1, &ebo_id);
	glBindVertexArray(0);

	if (!vao_id || !vbo_id || !ebo_id) {
		fprintf(stderr, "%s\n", glewGetErrorString(glGetError()));
		return false;
	}

	return true;
}


void free_glbuffers()
{
	glBindVertexArray(vao_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo_id);
	glDeleteBuffers(1, &ebo_id);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao_id);
	ebo_id = 0;
	vao_id = 0;
	vbo_id = 0;
}








} // namespace gp

