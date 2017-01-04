#include <stdio.h>
#include <vector>
#include <fstream>
#include <GL/glew.h>
#include "shader.hpp"
#include "finally.hpp"

namespace gp {

constexpr const auto kErrorMsgBufferSize = 1024;
static GLchar error_msg_buffer[kErrorMsgBufferSize];
static GLuint program_id = 0;
static GLuint vertex_shader_id = 0;
static GLuint fragment_shader_id = 0;

static std::string read_source(const char* filepath);
static bool compile_and_link(const std::string& vertex,
                             const std::string& fragment);
static bool validate_compilation(GLuint shader_id);
static bool validate_linkage(GLuint program_id);


bool initialize_shader()
{
	if ((program_id = glCreateProgram()) == 0) {
		fprintf(stderr, "%s\n", glewGetErrorString(glGetError()));
		return false;
	}

	const std::string vertex {read_source("shaders/vertex.glsl")};
	const std::string fragment {read_source("shaders/fragment.glsl")};

	if (!compile_and_link(vertex, fragment)) {
		terminate_shader();
		return false;
	}

	glUseProgram(program_id);
	return true;
}


void terminate_shader()
{	
	glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
	glDeleteProgram(program_id);
}

bool compile_and_link(const std::string& vertex, const std::string& fragment)
{
	vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	const char* sources[] { vertex.c_str(), fragment.c_str() };

	glShaderSource(vertex_shader_id, 1, &sources[0], nullptr);
	glCompileShader(vertex_shader_id);

	if (!validate_compilation(vertex_shader_id))
		return false;

	glShaderSource(fragment_shader_id, 1, &sources[1], nullptr);
	glCompileShader(fragment_shader_id);

	if (!validate_compilation(fragment_shader_id))
		return false;

	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
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


std::string read_source(const char* const filepath)
{
	std::ifstream file(filepath);
	
	if (!file.good())
		return "error";

	return { std::istreambuf_iterator<GLchar>(file),
	          std::istreambuf_iterator<GLchar>() };
}


} // namespace gp


