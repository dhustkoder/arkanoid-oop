#include <iostream>
#include <fstream>
#include "exception.hpp"
#include "shader.hpp"

namespace gp {

constexpr const size_t kErrorMsgBufferSize = 256;
static char error_msg_buffer[kErrorMsgBufferSize] { 0 };

static const char* get_compilation_error_msg(GLuint shader_id);
static const char* get_linker_error_msg(GLuint program_id);


Shader::Shader(const char* const vs_file_path, const char* const fs_file_path)
{
	using namespace std::string_literals;

	std::ifstream vs_file(vs_file_path, std::ios::binary | std::ios::ate);
	std::ifstream fs_file(fs_file_path, std::ios::binary | std::ios::ate);

	if (!vs_file.good())
		throw Exception("Can't open: "s + vs_file_path);
	else if (!fs_file.good())
		throw Exception("Can't open: "s + fs_file_path);
	
	std::string vs_source;
	std::string fs_source;

	vs_source.resize(static_cast<size_t>(vs_file.tellg()) + 1);
	fs_source.resize(static_cast<size_t>(fs_file.tellg()) + 1);

	vs_file.seekg(vs_file.beg);
	fs_file.seekg(fs_file.beg);
	
	std::copy(std::istreambuf_iterator<char>(vs_file),
	          std::istreambuf_iterator<char>(),
                  vs_source.begin());

	std::copy(std::istreambuf_iterator<char>(fs_file),
	          std::istreambuf_iterator<char>(),
	          fs_source.begin());


	m_programId = glCreateProgram();
	m_vsId = glCreateShader(GL_VERTEX_SHADER);
	m_fsId = glCreateShader(GL_FRAGMENT_SHADER);

	if (!m_programId || !m_vsId || !m_fsId) {
		const GLenum err = glGetError();
		throw Exception(std::string((char*)glewGetErrorString(err)));
	}

	const char* const sources[] {
		&vs_source[0],
		&fs_source[0]
	};
	
	glShaderSource(m_vsId, 1, &sources[0], nullptr);
	glShaderSource(m_fsId, 1, &sources[1], nullptr);
	glCompileShader(m_vsId);
	glCompileShader(m_fsId);

	const char* err_msg;

	if ((err_msg = get_compilation_error_msg(m_vsId)))
		throw Exception("failed to compile "s + vs_file_path + ": " + err_msg);
	else if (err_msg = get_compilation_error_msg(m_fsId))
		throw Exception("failed to compile "s + fs_file_path + ": " + err_msg);

	glAttachShader(m_programId, m_vsId);
	glAttachShader(m_programId, m_fsId);
	glLinkProgram(m_programId);

	if ((err_msg = get_linker_error_msg(m_programId))) {
		throw Exception("failed to link shader program "s + 
		                 vs_file_path + " / " + fs_file_path +
		                 ": " + err_msg);
	}
}


Shader::~Shader()
{
	glDetachShader(m_programId, m_vsId);
	glDetachShader(m_programId, m_fsId);
	glDeleteShader(m_vsId);
	glDeleteShader(m_fsId);
	glDeleteProgram(m_programId);
}





const char* get_compilation_error_msg(const GLuint shader_id)
{
	GLint success;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		glGetShaderInfoLog(shader_id, kErrorMsgBufferSize,
		                   nullptr, error_msg_buffer);
		return error_msg_buffer;
	}

	return nullptr;
}


const char* get_linker_error_msg(const GLuint program_id)
{
	const auto has_error = [program_id] {
		GLint success;	
		glGetProgramiv(program_id, GL_LINK_STATUS, &success);

		if (success == GL_FALSE) {
			glGetProgramInfoLog(program_id, kErrorMsgBufferSize,
			                    nullptr, error_msg_buffer);
			return true;
		}

		return false;
	};

	if (has_error())
		return error_msg_buffer;

	glValidateProgram(program_id);

	if (has_error())
		return error_msg_buffer;

	return nullptr;
}


} // namespace gp
