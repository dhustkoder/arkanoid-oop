#ifndef ARKANOID_OOP_PLAYER_HPP_
#define ARKANOID_OOP_PLAYER_HPP_
#include "keyboard.hpp"
#include "sprite.hpp"

namespace gp {


class Player : public Sprite {
public:
	explicit Player(Texture&&) = delete;
	explicit Player(const Texture& texture);
	void update(float dt, int maxleft);
};


inline Player::Player(const Texture& texture)
	: Sprite(texture)
{

}


inline void Player::update(const float dt, const int maxleft)
{
	if (Keyboard::isKeyPressed(Keyboard::D))
		setOrigin(getOrigin() + getVelocity() * dt);
	else if (Keyboard::isKeyPressed(Keyboard::A))
		setOrigin(getOrigin() - getVelocity() * dt);

	if (getRight() > maxleft)
		setOrigin({getOrigin().x - (getRight() - maxleft), getOrigin().y});
	else if (getLeft() < 0.0f)
		setOrigin({getOrigin().x - getLeft(), getOrigin().y});
}


} // namespace gp
#endif

