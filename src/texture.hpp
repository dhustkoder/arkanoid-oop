#ifndef GPROJ_TEXTURE_HPP_
#define GPROJ_TEXTURE_HPP_
#include <GL/glew.h>

namespace gp {

class Texture {
public:
	Texture(const char* texturefile);
	Texture(Texture&& other) noexcept;
	~Texture();
	void enable() const;
	void disable() const;
private:
	GLuint m_textureId;
	int m_width, m_height;
};


inline Texture::Texture(Texture&& other) noexcept
	: m_textureId(other.m_textureId),
	m_width(other.m_width), m_height(other.m_height)
{
	other.m_textureId = 0;
}

inline void Texture::enable() const
{
	glBindTexture(GL_TEXTURE_2D, m_textureId);
}


inline void Texture::disable() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


} // namespace gp
#endif

