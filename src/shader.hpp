#ifndef GPROJ_SHADER_HPP_
#define GPROJ_SHADER_HPP_
#include <GL/glew.h>


namespace gp {

	
class Shader {
public:
	Shader(const char* vs_file, const char* fs_file);
	~Shader();
	void enable() const { glUseProgram(m_programId); };
	void disable() const { glUseProgram(0); };
private:
	GLuint m_programId;
	GLuint m_vsId;
	GLuint m_fsId;
};


} // namespace gp
#endif
