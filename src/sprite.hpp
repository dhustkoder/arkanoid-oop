#ifndef GPROJ_SPRITE_HPP_
#define GPROJ_SPRITE_HPP_
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "texture.hpp"


namespace gp {


class Sprite {
public:

	Sprite(Sprite&&) noexcept = default;
	Sprite(const Sprite&) noexcept = default;


	Sprite(const glm::vec2& pos, const glm::vec2& size,
	       const glm::vec2& uv_pos, const glm::vec2& uv_size,
	       const glm::vec4& color, Texture& texture) noexcept;

	Sprite(const glm::vec2& pos, const glm::vec2& size,
		int uv_x_start, int uv_x_end, int uv_y_start, int uv_y_end,
		const glm::vec4& color, Texture& texture) noexcept;

	

	const glm::vec2& getPosition() const;
	const glm::vec2& getSize() const;
	const glm::vec2& getUVPos() const;
	const glm::vec2& getUVSize() const;
	const glm::vec4& getColor() const;
	const Texture& getTexture() const;
	GLfloat getTop() const;
	GLfloat getRight() const;
	GLfloat getBottom() const;
	GLfloat getLeft() const;
	
	void setPosition(const glm::vec2& newpos);
	void setSize(const glm::vec2& newsize);
	void setColor(const glm::vec4& newcolor);
private:
	glm::vec2 m_pos;
	glm::vec2 m_size;
	glm::vec2 m_uvPos;
	glm::vec2 m_uvSize;
	glm::vec4 m_color;
	Texture& m_texture;
};


inline Sprite::Sprite(const glm::vec2& pos, const glm::vec2& size,
                      const glm::vec2& uv_pos, const glm::vec2& uv_size,
		      const glm::vec4& color, Texture& texture) noexcept
	: m_pos(pos),
	m_size(size),
	m_uvPos(uv_pos),
	m_uvSize(uv_size),
	m_color(color),
	m_texture(texture)
{

}


inline Sprite::Sprite(const glm::vec2& pos, const glm::vec2& size,
		const int uv_x_start, const int uv_x_end,
		const int uv_y_start, const int uv_y_end,
		const glm::vec4& color, Texture& texture) noexcept
	: m_pos(pos),
	m_size(size),
	m_uvPos((float)uv_x_start / (float)texture.getWidth(), (float)uv_y_start / (float)texture.getHeight()),
	m_uvSize(((float)(uv_x_end + 1) - uv_x_start) / (float)texture.getWidth(), (((float)uv_y_end + 1) - uv_y_start) / (float)texture.getHeight()),
	m_color(color),
	m_texture(texture)
{
	
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


inline const glm::vec2& Sprite::getUVPos() const
{
	return m_uvPos;
}


inline const glm::vec2& Sprite::getUVSize() const
{
	return m_uvSize;
}


inline const Texture& Sprite::getTexture() const
{
	return m_texture;
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

