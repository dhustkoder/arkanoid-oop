#include <stdio.h>
#include <stddef.h>
#include <SOIL/SOIL.h>
#include "array.hpp"
#include "renderer.hpp"
#include "finally.hpp"

namespace gp {


GLuint vao_id = 0;
GLuint vbo_id = 0;
GLuint ebo_id = 0;

Array<Vertices> vertexbuffers = make_array<Vertices>();
Array<Elements> elementbuffers = make_array<Elements>();

Vertices bound_vertex_buffer { nullptr, 0 };
Elements bound_element_buffer { { nullptr, 0 }, { nullptr, 0 } };

GLuint textures_ids[kMaxTextures] { 0 };

GLuint programs_ids[kMaxShaders] { 0 };
ShaderLocs shaders_locs[kMaxShaders];
ShaderIds shaders_ids[kMaxShaders];
static GLchar error_msg_buffer[kErrorMsgBufferSize] { 0 };


static bool create_glbuffers();
static bool create_textures(const TexturesFiles& textures_files);
static bool create_shaders(const ShadersProgramsFiles& programs);
static void free_glbuffers();
static void free_textures();
static void free_shaders();


void fill_vbo(const Vertex* const vertices, const int count);

static bool read_sources(const char* vertexfilepath, const char* fragmentfilepath,
                         char* vertexsource, char* fragmentsource, int size);

static bool push_new_shader_program(const char* vertexfile, const char* fragmentfile, int index);
static bool validate_compilation(GLuint shader_id);
static bool validate_linkage(GLuint program_id);



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


bool create_textures(const TexturesFiles& textures_files)
{
	const int num_textures = textures_files.count;

	if (num_textures > kMaxTextures) {
		fprintf(stderr, "Max textures: %i\n", kMaxTextures);
		return false;
	}

	glGenTextures(num_textures, textures_ids);

	for (int i = 0; i < num_textures; ++i) {
		const auto tex_id = textures_ids[i];
		const char* const tex_file = textures_files.files[i];

		glBindTexture(GL_TEXTURE_2D, tex_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height;
		unsigned char* const image = SOIL_load_image(tex_file,
                                                             &width, &height,
		                                             nullptr, SOIL_LOAD_RGB);

		if (image == nullptr) {
			fprintf(stderr, "Couldn't load texture \'%s\' %s\n", tex_file, SOIL_last_result());
			return false;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}


void free_textures()
{
	unbind_textures();
	glDeleteTextures(kMaxTextures, textures_ids);
}


bool create_shaders(const ShadersProgramsFiles& programs)
{
	const int programs_count = programs.count;

	if (programs_count > kMaxShaders) {
		fprintf(stderr, "Max shaders: %i\n", kMaxShaders);
		return false;
	}

	for (int i = 0; i < programs_count; ++i) {
		if (!push_new_shader_program(programs.vertex[i], programs.fragment[i], i))
			return false;
		shaders_locs[i].view = glGetUniformLocation(programs_ids[i], "view");
		shaders_locs[i].model = glGetUniformLocation(programs_ids[i], "model");
		shaders_locs[i].projection = glGetUniformLocation(programs_ids[i], "projection");
	}

	return true;
}


void free_shaders()
{
	unbind_shaders();
	for (int i = 0; i < kMaxShaders; ++i) {
		const auto program_id = programs_ids[i];
		if (program_id == 0)
			break;
		
		const auto vertex_id = shaders_ids[i].vertex;
		const auto fragment_id = shaders_ids[i].fragment;

		glDetachShader(program_id, vertex_id);
		glDetachShader(program_id, fragment_id);
		glDeleteShader(vertex_id);
		glDeleteShader(fragment_id);
		glDeleteProgram(program_id);	
	}
}


bool push_new_shader_program(const char* vertexfile, const char* fragmentfile, const int index)
{
	char vertexsource[512];
	char fragmentsource[512];

	if (!read_sources(vertexfile, fragmentfile, vertexsource, fragmentsource, 512))
		return false;

	const char* sources[] {
		&vertexsource[0],
		&fragmentsource[0]
	};

	const auto program_id = glCreateProgram();
	const auto vertex_id = glCreateShader(GL_VERTEX_SHADER);
	const auto fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

	programs_ids[index] = program_id;
	shaders_ids[index].vertex = vertex_id;
	shaders_ids[index].fragment = fragment_id;

	glShaderSource(vertex_id, 1, &sources[0], nullptr);
	glCompileShader(vertex_id);

	if (!validate_compilation(vertex_id))
		return false;

	glShaderSource(fragment_id, 1, &sources[1], nullptr);
	glCompileShader(fragment_id);

	if (!validate_compilation(fragment_id))
		return false;

	glAttachShader(program_id, vertex_id);
	glAttachShader(program_id, fragment_id);
	glLinkProgram(program_id);

	if (!validate_linkage(program_id))
		return false;

	return true;
}


bool validate_compilation(const GLuint shader_id)
{
	GLint success;
	
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		glGetShaderInfoLog(shader_id, kErrorMsgBufferSize,
		                   nullptr, error_msg_buffer);
		fprintf(stderr, "%s\n", error_msg_buffer);
		return false;
	}

	return true;
}


bool validate_linkage(const GLuint program)
{
	const auto has_error = [program] {
		GLint success;	
		
		glGetProgramiv(program, GL_LINK_STATUS, &success);

		if (success == GL_FALSE) {
			glGetProgramInfoLog(program, kErrorMsgBufferSize,
			                    nullptr, error_msg_buffer);
			fprintf(stderr, "%s\n", error_msg_buffer);
			return true;
		}

		return false;
	};

	if (has_error())
		return true;

	glValidateProgram(program);
	return has_error() == false;
}


bool read_sources(const char* vertexfilepath,
                  const char* fragmentfilepath,
                  char* const vertexsource,
                  char* const fragmentsource,
                  const int size)
{
	FILE* const vertexfile = fopen(vertexfilepath, "r");
	if (vertexfile == nullptr) {
		fprintf(stderr, "Couldn't read \'%s\' source file\n", vertexfilepath);
		return false;
	}

	const auto vertexfile_guard = finally([vertexfile] {
		fclose(vertexfile);
	});



	FILE* const fragmentfile = fopen(fragmentfilepath, "r");

	if (fragmentfile == nullptr) {
		fprintf(stderr, "Couldn't read \'%s\' source file\n", fragmentfilepath);
		return false;
	}

	const auto fragmentfile_guard = finally([fragmentfile] {
		fclose(fragmentfile);
	});

	fseek(vertexfile, 0, SEEK_END);
	fseek(fragmentfile, 0, SEEK_END);
	
	const auto vertexsize = ftell(vertexfile);
	const auto fragmentsize = ftell(fragmentfile);

	if (vertexsize >= size || fragmentsize >= size) {
		fprintf(stderr, "Shader files are too big, max size: %i\n", size);
		return false;
	}

	fseek(vertexfile, 0, SEEK_SET);
	fseek(fragmentfile, 0, SEEK_SET);

	fread(vertexsource, 1, vertexsize, vertexfile);
	fread(fragmentsource, 1, fragmentsize, fragmentfile);

	vertexsource[vertexsize - 1] = '\0';
	fragmentsource[fragmentsize - 1] = '\0';

	return true;
}


} // namespace gp

