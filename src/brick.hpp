#ifndef ARKANOID_OOP_BRICK_HPP_
#define ARKANOID_OOP_BRICK_HPP_
#include "sprite.hpp"


namespace gp {


class Brick : public Sprite {
public:
	explicit Brick(Sprite&& sprite);

	void destroy();
	bool isDestroyed() const;

private:
	bool m_destroyed;
};


inline Brick::Brick(Sprite&& sprite)
	: Sprite(std::move(sprite)),
	m_destroyed(false)
{
}


inline void Brick::destroy()
{
	m_destroyed = true;
}


inline bool Brick::isDestroyed() const
{
	return m_destroyed;
}


} // namespace gp
#endif
