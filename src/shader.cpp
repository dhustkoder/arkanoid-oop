#include <iostream>
#include <string>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include "exception.hpp"
#include "finally.hpp"
#include "shader.hpp"


namespace gp {

constexpr const size_t kErrorMsgBufferSize = 256;
static char error_msg_buffer[kErrorMsgBufferSize] { 0 };

static const char* get_compilation_error_msg(GLuint shader_id);
static const char* get_linker_error_msg(GLuint program_id);


Shader::Shader(const char* const vs_file_path, const char* const fs_file_path)
{
	std::ifstream vs_file(vs_file_path, std::ios::binary | std::ios::ate);
	std::ifstream fs_file(fs_file_path, std::ios::binary | std::ios::ate);

	if (!vs_file.good())
		throw Exception(std::string("Can't open: ") + vs_file_path);
	else if (!fs_file.good())
		throw Exception(std::string("Can't open: ") + fs_file_path);
	
	std::string vs_source;
	std::string fs_source;

	vs_source.resize(static_cast<size_t>(vs_file.tellg()));
	fs_source.resize(static_cast<size_t>(fs_file.tellg()));

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

	auto failure_guard = finally([this] {
		this->freeShader();
	});


	if (!m_programId || !m_vsId || !m_fsId) {
		const GLenum err = glGetError();
		throw Exception(std::string((char*)glewGetErrorString(err)));
	}

	const char* const sources[] {
		vs_source.c_str(),
		fs_source.c_str()
	};
	
	glShaderSource(m_vsId, 1, &sources[0], nullptr);
	glShaderSource(m_fsId, 1, &sources[1], nullptr);
	glCompileShader(m_vsId);
	glCompileShader(m_fsId);

	const char* err_msg;

	if ((err_msg = get_compilation_error_msg(m_vsId))) {
		throw Exception(std::string("failed to compile ") + vs_file_path + ": " + err_msg);
	} else if ((err_msg = get_compilation_error_msg(m_fsId))) {
		throw Exception(std::string("failed to compile ") + fs_file_path + ": " + err_msg);
	}

	glAttachShader(m_programId, m_vsId);
	glAttachShader(m_programId, m_fsId);
	glLinkProgram(m_programId);

	if ((err_msg = get_linker_error_msg(m_programId))) {
		throw Exception(std::string("failed to link shader program ") + 
		                 vs_file_path + " / " + fs_file_path +
		                 ": " + err_msg);
	}

	failure_guard.abort();
}


void Shader::freeShader() noexcept
{
	glDetachShader(m_programId, m_vsId);
	glDetachShader(m_programId, m_fsId);
	glDeleteShader(m_vsId);
	glDeleteShader(m_fsId);
	glDeleteProgram(m_programId);
}



void Shader::setUniformMat4(const GLchar* const name, const glm::mat4& mat)
{
	const GLint loc = glGetUniformLocation(m_programId, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}


void Shader::setUniform1iv(const GLchar* const name, const GLint* const values, const int count)
{
	const GLint loc = glGetUniformLocation(m_programId, name);
	glUniform1iv(loc, count, values);
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
