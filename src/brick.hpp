#ifndef GPROJ_BRICK_HPP_
#define GPROJ_BRICK_HPP_
#include "sprite.hpp"


namespace gp {


class Brick : public Sprite {
public:
	Brick(const Sprite& sprite);

	void destroy();
	bool isDestroyed() const;

private:
	bool m_destroyed;
};


inline Brick::Brick(const Sprite& sprite)
	: Sprite(sprite),
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
