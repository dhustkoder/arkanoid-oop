#ifndef GPROJ_TEXTURE_HPP_
#define GPROJ_TEXTURE_HPP_
#include <GL/glew.h>

namespace gp {

class Texture {
public:
	Texture(const char* texturefile);
	~Texture();
	void enable() { glBindTexture(GL_TEXTURE_2D, m_textureId); }
	void disable() { glBindTexture(GL_TEXTURE_2D, 0); }
private:
	GLuint m_textureId;
	int m_width, m_height;
};


} // namespace gp
#endif
