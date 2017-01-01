#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "shader.hpp"
#include "finally.hpp"

namespace gp {

constexpr const auto kErrorMsgBufferSize = 1024;
static GLchar s_error_msg_buffer[kErrorMsgBufferSize];


static GLchar* read_source(const char* filepath);

static bool compile_and_link(const GLchar* const* sources,
                             const GLenum* types,
			     long count,
			     Shader* program);

static bool check_compile_errors(GLuint shader_id);
static bool validate_program(GLuint program_id);




Shader* create_shader(const char* const* const filepaths,
                      const GLenum* const types,
                      const long count)
{
	GLchar** const sources =
	  static_cast<GLchar**>(calloc(count, sizeof(GLchar*)));

	if (sources == nullptr)
		return nullptr;

	const auto sources_guard = finally([sources, count] {
		for (long i = 0; i < count; ++i)
			free(sources[i]);
		free(sources);
	});

	for (long i = 0; i < count; ++i) {
		if ((sources[i] = read_source(filepaths[i])) == nullptr)
			return nullptr;
	}

	const auto memsize = sizeof(Shader) + sizeof(GLuint) * count;
	Shader* const program = static_cast<Shader*>(malloc(memsize));
	
	if (program == nullptr) {
		perror("");
		return nullptr;
	}

	auto program_guard = finally([program] {
		free(program);	
	});

	if ((program->id = glCreateProgram()) == 0) {
		fprintf(stderr, "%s\n", glewGetErrorString(glGetError()));
		return nullptr;
	}

	auto program_id_guard = finally([program] {
		glDeleteProgram(program->id);
	});

	program->count = count;

	if (!compile_and_link(sources, types, count, program))
		return nullptr;

	program_id_guard.Abort();
	program_guard.Abort();
	return program;
}


void destroy_shader(Shader* const program)
{	
	for (long i = 0; i < program->count; ++i) {
		glDetachShader(program->id, program->shaders[i]);
		glDeleteShader(program->shaders[i]);
	}

	glDeleteProgram(program->id);
	free(program);
}


bool compile_and_link(const GLchar* const* sources,
		      const GLenum* const types,
		      const long count,
		      Shader* const program)
{
	memset(program->shaders, 0, sizeof(GLuint) * count);
	
	auto shaders_guard = finally([program, count] {
		for (long i = 0; i < count; ++i) {
			glDetachShader(program->id, program->shaders[i]);
			glDeleteShader(program->shaders[i]);
		}
	});

	for (long i = 0; i < count; ++i) {
		if ((program->shaders[i] = glCreateShader(types[i])) == 0)
			return false;

		glShaderSource(program->shaders[i], 1, &sources[i], nullptr);
		glCompileShader(program->shaders[i]);

		if (check_compile_errors(program->shaders[i]))
			return false;

		glAttachShader(program->id, program->shaders[i]);
	}

	glLinkProgram(program->id);

	if (!validate_program(program->id))
		return false;

	shaders_guard.Abort();
	return true;
}


bool check_compile_errors(const GLuint shader_id)
{
	GLint success;
	
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		glGetShaderInfoLog(shader_id, kErrorMsgBufferSize,
		                   nullptr, s_error_msg_buffer);
		fprintf(stderr, "%s\n", s_error_msg_buffer);
		return true;
	}

	return false;
}


bool validate_program(const GLuint program)
{
	const auto has_error = [program] {
		GLint success;	
		
		glGetProgramiv(program, GL_LINK_STATUS, &success);

		if (success == GL_FALSE) {
			glGetProgramInfoLog(program, kErrorMsgBufferSize,
			                    nullptr, s_error_msg_buffer);
			fprintf(stderr, "%s\n", s_error_msg_buffer);
			return true;
		}

		return false;
	};

	if (has_error())
		return true;

	glValidateProgram(program);
	return has_error() == false;
}


GLchar* read_source(const char* const filepath)
{
	FILE* const file = fopen(filepath, "rt");

	if (file == nullptr) {
		const auto errcode = errno;
		fprintf(stderr, "Couldn't open shader source \'%s\': %s\n",
		        filepath, strerror(errcode));
		return nullptr;
	}

	const auto file_guard = finally([file] {
		fclose(file);
	});

	fseek(file, 0, SEEK_END);

	const auto filesize = static_cast<size_t>(ftell(file));
	
	GLchar* const source =
	  static_cast<GLchar*>(calloc(filesize + 1, sizeof(GLchar)));
	
	if (source == nullptr)
		return nullptr;
	
	auto source_guard = finally([source] {
		free(source);
	});

	fseek(file, 0, SEEK_SET);

	if (fread(source, sizeof(GLchar), filesize, file) < filesize) {
		const auto errcode = errno;
		fprintf(stderr, "Error while reading shader source "
		                "\'%s\' : %s\n", filepath, strerror(errcode));
		return nullptr;
	}

	source_guard.Abort();
	return source;
}


} // namespace gp
