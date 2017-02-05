#ifndef ARKANOID_OOP_SPRITE_HPP_
#define ARKANOID_OOP_SPRITE_HPP_
#include "math_types.hpp"
#include "texture.hpp"


namespace gp {


class Sprite {
public:
	explicit Sprite(Sprite&&) noexcept = default;
	explicit Sprite(const Sprite&) noexcept = default;

	Sprite& operator=(Sprite&&) noexcept = default;
	Sprite& operator=(const Sprite&) noexcept = default;


	Sprite(const Texture& texture, const Vec2f& origin, const Vec2f& size,
	       const Vec2f& uv_pos, const Vec2f& uv_size,
	       const Vec4f& color = Vec4f{1, 1, 1, 1}) noexcept;

	explicit Sprite(const Texture& texture) noexcept;

	
	const Vec2f& getOrigin() const;
	Vec2f getSize() const;
	const Vec2f& getHalfSize() const;
	const Vec2f& getNormalizedUVPosition() const;
	const Vec2f& getNormalizedUVSize() const;
	const Vec4f& getColor() const;
	const Texture& getTexture() const;

	GLfloat getTop() const;
	GLfloat getRight() const;
	GLfloat getBottom() const;
	GLfloat getLeft() const;
	
	void flipHorizontally();
	void flipVertically();

	void setOrigin(const Vec2f& neworigin);
	void setSize(const Vec2f& newsize);
	void setUVSize(const Vec2f& new_uv_size);
	void setUVPos(const Vec2f& new_uv_pos);
	void setColor(const Vec4f& newcolor);

private:
	Vec2f m_origin;
	Vec2f m_size;
	Vec2f m_uvPos;
	Vec2f m_uvSize;
	Vec4f m_color;
	const Texture* m_texture;
};



inline Sprite::Sprite(const Texture& texture,
                      const Vec2f& origin, const Vec2f& size,
                      const Vec2f& uv_pos, const Vec2f& uv_size,
		      const Vec4f& color) noexcept
	: m_origin(origin),
	m_size(size * 0.5f),
	m_color(color),
	m_texture(&texture)
{
	const GLfloat w = static_cast<GLfloat>(m_texture->getWidth());
	const GLfloat h = static_cast<GLfloat>(m_texture->getHeight());

	// normalize uv position and size
	m_uvPos = { uv_pos.x / w, uv_pos.y / h };
	m_uvSize = { uv_size.x / w, uv_size.y / h };
}


inline Sprite::Sprite(const Texture& texture) noexcept
	: m_color(1, 1, 1, 1),
	m_texture(&texture)
{

}


inline const Vec2f& Sprite::getOrigin() const
{
	return m_origin;
}


inline Vec2f Sprite::getSize() const
{
	return m_size * 2.0f;
}


inline const Vec2f& Sprite::getHalfSize() const
{
	return m_size;
}


inline const Vec2f& Sprite::getNormalizedUVPosition() const
{
	return m_uvPos;
}


inline const Vec2f& Sprite::getNormalizedUVSize() const
{
	return m_uvSize;
}


inline const Vec4f& Sprite::getColor() const
{
	return m_color;
}


inline const Texture& Sprite::getTexture() const
{
	return *m_texture;
}


inline GLfloat Sprite::getTop() const
{
	return m_origin.y - m_size.y;
}


inline GLfloat Sprite::getRight() const
{
	return m_origin.x + m_size.x;
}


inline GLfloat Sprite::getBottom() const
{
	return m_origin.y + m_size.y;
}


inline GLfloat Sprite::getLeft() const
{
	return m_origin.x - m_size.x;
}


inline void Sprite::flipHorizontally()
{
	m_uvPos.x += m_uvSize.x;
	m_uvSize.x = -m_uvSize.x;
}


inline void Sprite::flipVertically()
{
	m_uvPos.y += m_uvSize.y;
	m_uvSize.y = -m_uvSize.y;
}


inline void Sprite::setOrigin(const Vec2f& neworigin)
{
	m_origin = neworigin;
}


inline void Sprite::setSize(const Vec2f& newsize)
{
	m_size = newsize * 0.5f;
}


inline void Sprite::setUVSize(const Vec2f& new_uv_size)
{
	m_uvSize = new_uv_size / Vec2f{ m_texture->getWidth(), m_texture->getHeight() };
}


inline void Sprite::setUVPos(const Vec2f& new_uv_pos)
{
	m_uvPos = new_uv_pos / Vec2f{ m_texture->getWidth(), m_texture->getHeight() };
}


inline void Sprite::setColor(const Vec4f& newcolor)
{
	m_color = newcolor;
}


} // namespace gp
#endif

