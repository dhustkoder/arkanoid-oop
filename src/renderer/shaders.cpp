#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "memory/array.hpp"
#include "utils/finally.hpp"
#include "shaders.hpp"


namespace gp {


GLuint programs_ids[kMaxShaders] { 0 };
ShaderLocs shaders_locs[kMaxShaders];
ShaderIds shaders_ids[kMaxShaders];
static GLchar error_msg_buffer[kErrorMsgBufferSize] { 0 };


bool read_sources(const char* vertexfilepath, const char* fragmentfilepath,
                  Array<char>* vertexsource, Array<char>* fragmentsource);

static bool push_new_shader_program(const char* vertexfile, const char* fragmentfile, int index);
static bool validate_compilation(GLuint shader_id);
static bool validate_linkage(GLuint program_id);


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
		shaders_locs[i].light_color = glGetUniformLocation(programs_ids[i], "light_color");
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
	Array<char> vertexsource;
	Array<char> fragmentsource;

	if (!read_sources(vertexfile, fragmentfile, &vertexsource, &fragmentsource))
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


bool read_sources(const char* const vertexfilepath,
                  const char* const fragmentfilepath,
                  Array<char>* const vertexsource,
                  Array<char>* const fragmentsource)
{
	const char* filepaths[] { vertexfilepath, fragmentfilepath };
	Array<char>* sources[] { vertexsource, fragmentsource };
	constexpr auto numfiles = sizeof(filepaths)/sizeof(filepaths[0]);
	constexpr auto numsources = sizeof(sources)/sizeof(sources[0]);
	static_assert(numfiles == numsources && numfiles < INT_MAX, "");

	for (int i = 0; i < numfiles; ++i) {
		FILE* const file = fopen(filepaths[i], "r");

		if (file == nullptr) {
			const int err = errno;
			fprintf(stderr, "Couldn't read \'%s\' source file: %s\n",
		                filepaths[i], strerror(err));
			return false;
		}

		const auto fileguard = finally([file] {
			fclose(file);
		});

		Array<char>& source = *sources[i];

		fseek(file, 0, SEEK_END);
		const long filesize = ftell(file);
		fseek(file, 0, SEEK_SET);

		resize(filesize, &source);
		fread(&source[0], 1, filesize, file);

		source[filesize - 1] = '\0';
	}

	return true;
}

}