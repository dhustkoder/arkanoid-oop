#ifndef ARKANOID_OOP_BRICK_HPP_
#define ARKANOID_OOP_BRICK_HPP_
#include "sprite.hpp"


namespace gp {


class Brick : public Sprite {
public:
	Brick(Texture&&) = delete;
	
	Brick(const Texture& texture);
	void destroy();
	bool isDestroyed() const;

private:
	bool m_destroyed;
};


inline Brick::Brick(const Texture& texture)
	: Sprite(texture), m_destroyed(false)
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


}
#endif

