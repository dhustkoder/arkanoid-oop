#ifndef ARKANOID_OOP_TEXTURE_HPP_
#define ARKANOID_OOP_TEXTURE_HPP_
#include <string>
#include <utility>
#include <GL/glew.h>
#include "math_types.hpp"

namespace gp {


class Texture {
public:
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;


	Texture(const std::string& texture_file_path);
	Texture(Texture&& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;
	~Texture();


	void enable() const;
	void disable() const;


	GLuint getId() const;
	int getIndex() const;
	int getWidth() const;
	int getHeight() const;
	Vec2f getSize() const;

private:
	GLuint m_id;
	int m_width, m_height;
	int m_index;
	static int s_index;
};


inline Texture::Texture(Texture&& other) noexcept
	: m_id(other.m_id),
	m_width(other.m_width),
	m_height(other.m_height),
	m_index(other.m_index)
{
	other.m_id = 0;
	other.m_width = 0;
	other.m_height = 0;
	other.m_index = 0;
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
	std::swap(m_index, other.m_index);
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


inline int Texture::getWidth() const
{
	return m_width;
}


inline int Texture::getHeight() const
{
	return m_height;
}


inline Vec2f Texture::getSize() const
{
	return { getWidth(), getHeight() };
}


} // namespace gp
#endif

