#ifndef ARKANOID_OOP_BRICK_HPP_
#define ARKANOID_OOP_BRICK_HPP_
#include "sprite.hpp"


namespace gp {


class Brick : public Sprite {
public:
	Brick(Texture&&) = delete;
	
	explicit Brick(const Texture& t)
		: Sprite(t)
	{
	}
};


} // namespace gp
#endif
