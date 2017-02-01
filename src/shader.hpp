#ifndef GPROJ_SHADER_HPP_
#define GPROJ_SHADER_HPP_
#include <GL/glew.h>
#include <glm/mat4x4.hpp>

namespace gp {

	
class Shader {
public:
	Shader(const char* vs_file, const char* fs_file);
	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;
	~Shader();
	
	void enable() const;
	void disable() const;

	void setUniformMat4(const GLchar* name, const glm::mat4& mat);
	void setUniformIv(const GLchar* name, const GLint* values, int count);
private:
	void freeShader() noexcept;
private:
	GLuint m_programId;
	GLuint m_vsId;
	GLuint m_fsId;
};


inline Shader::Shader(Shader&& other) noexcept
	: m_programId(other.m_programId),
	m_vsId(other.m_vsId),
	m_fsId(other.m_fsId)
{
	other.m_programId = 0;
	other.m_vsId = 0;
	other.m_fsId = 0;
}


inline Shader& Shader::operator=(Shader&& other) noexcept
{
	std::swap(m_programId, other.m_programId);
	std::swap(m_vsId, other.m_vsId);
	std::swap(m_fsId, other.m_fsId);
	return *this;
}


inline void Shader::enable() const
{
	glUseProgram(m_programId);
}


inline void Shader::disable() const
{
	glUseProgram(0);
}


} // namespace gp
#endif
