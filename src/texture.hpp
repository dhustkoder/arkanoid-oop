#ifndef GPROJ_TEXTURE_HPP_
#define GPROJ_TEXTURE_HPP_
#include <utility>
#include <GL/glew.h>

namespace gp {

class Texture {
public:
	Texture(const char* texturefile);
	Texture(Texture&& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;
	~Texture();
	void enable() const;
	void disable() const;
	GLuint getId() const;
	int getIndex() const;
private:
	GLuint m_id;
	int m_width, m_height;
	int m_index;
	static int s_index;
};


inline Texture::Texture(Texture&& other) noexcept
	: m_id(other.m_id),
	m_width(other.m_width),
	m_height(other.m_height)
{
	other.m_id = 0;
	other.m_width = 0;
	other.m_height = 0;
}


inline Texture::~Texture()
{
	if (m_id != 0)
		glDeleteTextures(1, &m_id);
}


inline Texture& Texture::operator=(Texture&& other) noexcept
{
	std::swap(m_id, other.m_id);
	std::swap(m_width, other.m_width);
	std::swap(m_height, other.m_height);
	return *this;
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


inline int Texture::getIndex() const
{
	return m_index;
}


} // namespace gp
#endif

