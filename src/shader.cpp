#include <stdio.h>
#include <fstream>
#include <GL/glew.h>
#include "shader.hpp"

namespace gp {

constexpr const auto kErrorMsgBufferSize = 1024;
static GLchar error_msg_buffer[kErrorMsgBufferSize];

std::vector<GLuint> programs_ids;
static std::vector<std::pair<GLuint, GLuint>> shaders_ids;

static bool read_sources(const std::string& vertex_file, const std::string& fragment_file,
                        std::string* vertex_source, std::string* fragment_source);

static bool compile_and_link(const std::string& vertex_file, const std::string& fragment_file);
static bool validate_compilation(GLuint shader_id);
static bool validate_linkage(GLuint program_id);


bool initialize_shader(const std::vector<std::pair<std::string, std::string>>& programs)
{
	programs_ids.reserve(programs.size());
	shaders_ids.reserve(programs.size());

	for (const auto& program : programs) {
		if (!compile_and_link(program.first, program.second)) {
			terminate_shader();
			return false;
		}
	}

	return true;
}


void terminate_shader()
{
	unbind_shader_program();	
	for (size_t i = 0; i < programs_ids.size(); ++i) {
		const auto program_id = programs_ids[i];
		const auto vertex_id = shaders_ids[i].first;
		const auto fragment_id = shaders_ids[i].second;

		glDetachShader(program_id, vertex_id);
		glDetachShader(program_id, fragment_id);
		glDeleteShader(vertex_id);
		glDeleteShader(fragment_id);
		glDeleteProgram(program_id);	
	}

	programs_ids.clear();
	shaders_ids.clear();
}


bool compile_and_link(const std::string& vertex_file, const std::string& fragment_file)
{
	std::string vertex_source, fragment_source;

	if (!read_sources(vertex_file, fragment_file,
	                  &vertex_source, &fragment_source)) {
		return false;
	}

	const char* sources[] {
		vertex_source.c_str(),
		fragment_source.c_str()
	};

	const auto program_id = glCreateProgram();
	const auto vertex_id = glCreateShader(GL_VERTEX_SHADER);
	const auto fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
	programs_ids.push_back(program_id);
	shaders_ids.push_back({vertex_id, fragment_id});

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


bool read_sources(const std::string& vertex_filepath, const std::string& fragment_filepath,
                 std::string* const vertex_source, std::string* const fragment_source)
{
	std::ifstream vertex_file(vertex_filepath);
	std::ifstream fragment_file(fragment_filepath);
	
	if (!vertex_file.good()) {
		fprintf(stderr, "Couldn't read \'%s\' source file\n",
		        vertex_filepath.c_str());
		return false;
	} else if (!fragment_file.good()) {
		fprintf(stderr, "Couldn't read \'%s\' source file\n",
		        fragment_filepath.c_str());
		return false;
	}

	*vertex_source =
	  std::string{ std::istreambuf_iterator<GLchar>(vertex_file),
	               std::istreambuf_iterator<GLchar>() };

	*fragment_source =
	  std::string{ std::istreambuf_iterator<GLchar>(fragment_file),
	               std::istreambuf_iterator<GLchar>() };

	return true;
}


} // namespace gp


