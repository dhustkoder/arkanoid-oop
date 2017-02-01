#ifndef GPROJ_SPRITE_HPP_
#define GPROJ_SPRITE_HPP_
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "texture.hpp"


namespace gp {


class Sprite {
public:
	Sprite(Texture&& texture, const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color) noexcept;
	const Texture& getTexture() const;
	const glm::vec2& getPosition() const;
	const glm::vec2& getSize() const;
	const glm::vec4& getColor() const;
	GLfloat getTop() const;
	GLfloat getRight() const;
	GLfloat getBottom() const;
	GLfloat getLeft() const;
	
	void setPosition(const glm::vec2& newpos);
	void setSize(const glm::vec2& newsize);
	void setColor(const glm::vec4& newcolor);
private:
	Texture m_texture;
	glm::vec2 m_pos;
	glm::vec2 m_size;
	glm::vec4 m_color;
};


inline const Texture& Sprite::getTexture() const
{
	return m_texture;
}


inline const glm::vec2& Sprite::getPosition() const
{
	return m_pos;
}


inline const glm::vec2& Sprite::getSize() const
{
	return m_size;
}


inline const glm::vec4& Sprite::getColor() const
{
	return m_color;
}


inline GLfloat Sprite::getTop() const
{
	return m_pos.y + m_size.y;
}


inline GLfloat Sprite::getRight() const
{
	return m_pos.x + m_size.x;
}


inline GLfloat Sprite::getBottom() const
{
	return m_pos.y - m_size.y;
}


inline GLfloat Sprite::getLeft() const
{
	return m_pos.x - m_size.x;
}


inline void Sprite::setPosition(const glm::vec2& newpos)
{
	m_pos = newpos;
}


inline void Sprite::setSize(const glm::vec2& newsize)
{
	m_size = newsize;
}


inline void Sprite::setColor(const glm::vec4& newcolor)
{
	m_color = newcolor;
}


} // namespace gp
#endif

