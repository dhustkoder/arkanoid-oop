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

Array<const Vertices*> vertexbuffers;
Array<const Elements*> elementbuffers;
const Vertices* bound_vertex_buffer = nullptr;
const Elements* bound_element_buffer = nullptr;


extern bool create_display(const char* title, int w, int h);
extern void free_display();

static bool create_glbuffers();
static void free_glbuffers();

extern bool create_textures(const TexturesFiles& textures_files);
extern void free_textures();

extern bool create_shaders(const ShadersProgramsFiles& programs);
extern void free_shaders();


bool initialize_renderer(const char* title,
                         const int width,
			 const int height,
			 const TexturesFiles& textures,
			 const ShadersProgramsFiles& shaders)
{
	auto failure_guard = finally([] {
		terminate_renderer();
	});

	if (!create_display(title, width, height) ||
	    !create_glbuffers() ||
	    !create_textures(textures) ||
	    !create_shaders(shaders))
		return false;

	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	constexpr const int infosize = 4;

	constexpr GLenum infonums[infosize] {
		GL_VENDOR, GL_RENDERER, GL_VERSION,
		GL_SHADING_LANGUAGE_VERSION
	};

	constexpr const char* const infostrs[infosize] {
		"VENDOR", "RENDERER", "VERSION",
		"SHADING LANGUAGE VERSION"
	};


	puts("OpenGL");
	for (int i = 0; i < infosize; ++i)
		printf("%s: %s\n", infostrs[i], glGetString(infonums[i]));

	failure_guard.Abort();
	return true;
}


void terminate_renderer()
{
	free_shaders();
	free_textures();
	free_glbuffers();
	free_display();
}


void fill_vbo(const Vertex* vertices, const int count)
{
	constexpr auto vertsize = sizeof(*vertices);
	const auto buffsize = vertsize * count;
	const auto pos_offset = (GLvoid*) offsetof(Vertex, pos);
	const auto tex_coords_offset = (GLvoid*) offsetof(Vertex, tex_coords);

	glBufferData(GL_ARRAY_BUFFER, buffsize, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, sizeof(Vertex::pos)/sizeof(GLfloat), GL_FLOAT, GL_FALSE, vertsize, pos_offset);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, sizeof(Vertex::tex_coords)/sizeof(GLfloat), GL_FLOAT, GL_FALSE, vertsize, tex_coords_offset);
	glEnableVertexAttribArray(1);
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

