#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shaders.hpp"

namespace gp {

constexpr const GLchar* const kVertexShader = "#version 400\n"
	"layout(location=0) in vec4 in_Position;\n"
	"layout(location=1) in vec4 in_Color;\n"
	"out vec4 ex_Color;\n"
	"void main(void)\n"
	"{\n"
	"	gl_Position = in_Position;\n"
	"	ex_Color = in_Color;\n"
	"}\n";

constexpr const GLchar* const kFragmentShader = "#version 400\n"
	"in vec4 ex_Color;\n"
	"out vec4 out_Color;\n"
	"void main(void)\n"
	"{\n"
	"	out_Color = ex_Color;\n"
	"}\n";


constexpr const auto kErrorMsgBufferSize = 1024;
static GLchar s_error_msg_buffer[kErrorMsgBufferSize];

static bool check_shader_compile_errors(GLuint shader_id);
static bool validate_shaders_program(GLuint program);
static bool compile_and_link_shaders(const GLchar* const * sources,
                                     const GLint* lengths,
		                     const GLenum* types,
		                     Shaders* shaders);

Shaders* create_shaders()
{
	constexpr const GLenum shader_types[] {
		GL_VERTEX_SHADER, GL_FRAGMENT_SHADER
	};
	constexpr const GLchar* const shader_sources[] {
		kVertexShader, kFragmentShader
	};
	const GLint lengths[] {
		static_cast<GLint>(strlen(kVertexShader)),
		static_cast<GLint>(strlen(kFragmentShader))
	};

	const auto num_of_shaders = sizeof(shader_types) / sizeof(GLenum);
	const auto memsize = sizeof(Shaders) + sizeof(GLuint) * num_of_shaders;

	Shaders* const shaders = static_cast<Shaders*>(malloc(memsize));
	
	if (shaders == nullptr) {
		perror("");
		return nullptr;
	}

	shaders->program = glCreateProgram();
	shaders->size = num_of_shaders;
	if (!compile_and_link_shaders(shader_sources, lengths,
				     shader_types, shaders)) {
		goto free_shaders;
	}

	return shaders;

free_shaders:
	glDeleteProgram(shaders->program);
	free(shaders);
	return nullptr;
}

void destroy_shaders(Shaders* const shaders)
{	
	for (long i = 0; i < shaders->size; ++i) {
		glDetachShader(shaders->program, shaders->ids[i]);
		glDeleteShader(shaders->ids[i]);
	}

	glDeleteProgram(shaders->program);
	free(shaders);
}

bool compile_and_link_shaders(
                     const GLchar* const * const sources,
                     const GLint* const lengths,
		     const GLenum* const types,
		     Shaders* const shaders)
{
	long i;
	for (i = 0; i < shaders->size; ++i) {
		
		if ((shaders->ids[i] = glCreateShader(types[i])) == 0)
			goto free_ids;

		glShaderSource(shaders->ids[i], 1, &sources[i], &lengths[i]);
		glCompileShader(shaders->ids[i]);

		if (check_shader_compile_errors(shaders->ids[i]))
			goto free_ids;

		glAttachShader(shaders->program, shaders->ids[i]);
	}

	glLinkProgram(shaders->program);
	if (!validate_shaders_program(shaders->program))
		goto free_ids;

	return true;

free_ids:
	long created_ids = i;
	for (i = 0; i < created_ids; ++i) {
		glDetachShader(shaders->program, shaders->ids[i]);
		glDeleteShader(shaders->ids[i]);
	}

	return false;
}

bool check_shader_compile_errors(const GLuint shader_id)
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

bool validate_shaders_program(const GLuint program)
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


} // namespace gp
