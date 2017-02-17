#ifndef ARKANOOP_BRICK_HPP_
#define ARKANOOP_BRICK_HPP_
#include "resource_manager.hpp"

namespace gp {


class Brick : public Sprite {
public:
	Brick (int resistence = 1);
	void hit(int force = 1);
	bool isDestroyed() const;

private:
	int m_resistence;
};


inline Brick::Brick(int resistence)
	: Sprite(ResourceManager::getSpriteSheet("bricks").getTexture()),
	m_resistence(resistence)
{
}


inline void Brick::hit(int force)
{
	m_resistence -= force;
}


inline bool Brick::isDestroyed() const
{
	return m_resistence <= 0;
}


}
#endif

