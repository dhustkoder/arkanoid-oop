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
	GLuint getId() const;
private:
	GLuint m_id;
	int m_width, m_height;
};


inline Texture::Texture(Texture&& other) noexcept
	: m_id(other.m_id),
	m_width(other.m_width), m_height(other.m_height)
{
	other.m_id = 0;
}

inline void Texture::enable() const
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}


inline void Texture::disable() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


inline GLuint Texture::getId() const
{
	return m_id;
}


} // namespace gp
#endif

