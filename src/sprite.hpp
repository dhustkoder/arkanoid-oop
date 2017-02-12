#ifndef ARKANOOP_SPRITE_HPP_
#define ARKANOOP_SPRITE_HPP_
#include "math_types.hpp"
#include "texture.hpp"


namespace gp {


class Sprite {
public:
	explicit Sprite(Texture&&) = delete;
	void setTexture(Texture&&) = delete;

	Sprite& operator=(Sprite&&) noexcept = default;
	Sprite& operator=(const Sprite&) noexcept = default;

	explicit Sprite(const Texture& texture) noexcept;

	Sprite(Sprite&& other) noexcept;
	Sprite(const Sprite& other) noexcept;

	Sprite(const Texture& texture, const Vec2f& origin, const Vec2f& size,
	       const Vec2f& uv_pos, const Vec2f& uv_size,
	       const Vec2f& velocity = {0, 0}, const Vec4f& color = Vec4f{1, 1, 1, 1}) noexcept;
	
	const Vec2f& getOrigin() const;
	Vec2f getSize() const;
	const Vec2f& getHalfSize() const;
	const Vec2f& getNormalizedUVPosition() const;
	const Vec2f& getNormalizedUVSize() const;
	const Vec2f& getVelocity() const;
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
	void setVelocity(const Vec2f& new_velocity);
	void setColor(const Vec4f& newcolor);
	void setTexture(const Texture& new_texture);

	// utils for derived classes
	void setSprite(const Sprite& sprite);
	void setSprite(Sprite&& sprite);
	const Sprite& getSprite() const;

	bool checkAABBCollision(const Sprite& other) const;

private:
	Vec2f m_origin;
	Vec2f m_size;
	Vec2f m_uvPos;
	Vec2f m_uvSize;
	Vec2f m_velocity;
	Vec4f m_color;
	const Texture* m_texture;
};


inline Sprite::Sprite(const Texture& texture) noexcept
	: m_origin(0),
	m_size(0),
	m_uvPos(0),
	m_uvSize(0),
	m_velocity(0, 0),
	m_color(1, 1, 1, 1),
	m_texture(&texture)
{

}


inline Sprite::Sprite(Sprite&& other) noexcept
	: m_origin(other.m_origin),
	m_size(other.m_size),
	m_uvPos(other.m_uvPos),
	m_uvSize(other.m_uvSize),
	m_velocity(other.m_velocity),
	m_color(other.m_color),
	m_texture(other.m_texture)
{

}


inline Sprite::Sprite(const Sprite& other) noexcept
	: m_origin(other.m_origin),
	m_size(other.m_size),
	m_uvPos(other.m_uvPos),
	m_uvSize(other.m_uvSize),
	m_velocity(other.m_velocity),
	m_color(other.m_color),
	m_texture(other.m_texture)
{

}


inline Sprite::Sprite(const Texture& texture,
                      const Vec2f& origin, const Vec2f& size,
                      const Vec2f& uv_pos, const Vec2f& uv_size,
		      const Vec2f& velocity, const Vec4f& color) noexcept
	: m_origin(origin),
	m_size(size / 2.0f),
	m_velocity(velocity),
	m_color(color),
	m_texture(&texture)
{
	const GLfloat w = static_cast<GLfloat>(m_texture->getWidth());
	const GLfloat h = static_cast<GLfloat>(m_texture->getHeight());

	// normalize uv position and size
	m_uvPos = { uv_pos.x / w, uv_pos.y / h };
	m_uvSize = { uv_size.x / w, uv_size.y / h };
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


inline const Vec2f& Sprite::getVelocity() const
{
	return m_velocity;
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
	m_size = (newsize / 2.0f);
}


inline void Sprite::setUVSize(const Vec2f& new_uv_size)
{
	m_uvSize = new_uv_size / Vec2f{ m_texture->getWidth(), m_texture->getHeight() };
}


inline void Sprite::setUVPos(const Vec2f& new_uv_pos)
{
	m_uvPos = new_uv_pos / Vec2f{ m_texture->getWidth(), m_texture->getHeight() };
}


inline void Sprite::setVelocity(const Vec2f& new_velocity)
{
	m_velocity = new_velocity;
}


inline void Sprite::setColor(const Vec4f& newcolor)
{
	m_color = newcolor;
}

inline void Sprite::setTexture(const Texture& new_texture)
{
	m_texture = &new_texture;
}


inline void Sprite::setSprite(const Sprite& sprite)
{
	this->operator=(sprite);
}


inline void Sprite::setSprite(Sprite&& sprite)
{
	this->operator=(std::move(sprite));
}


inline const Sprite& Sprite::getSprite() const
{
	return *this;
}


inline bool Sprite::checkAABBCollision(const Sprite& other) const
{
	return getRight() >= other.getLeft() &&
		getLeft() <= other.getRight() &&
		getTop()   <= other.getBottom() &&
		getBottom() >= other.getTop();
}


} // namespace gp
#endif

