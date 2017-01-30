#ifndef GPROJ_SHADER_HPP_
#define GPROJ_SHADER_HPP_
#include <GL/glew.h>
#include <glm/mat4x4.hpp>

namespace gp {

	
class Shader {
public:
	Shader(const char* vs_file, const char* fs_file);
	~Shader();
	
	void enable() const;
	void disable() const;

	void setUniformMat4(const GLchar* name, const glm::mat4& mat);

private:
	void freeShader() noexcept;
private:
	GLuint m_programId;
	GLuint m_vsId;
	GLuint m_fsId;
};


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
