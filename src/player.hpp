#ifndef ARKANOID_OOP_PLAYER_HPP_
#define ARKANOID_OOP_PLAYER_HPP_
#include "keyboard.hpp"
#include "sprite.hpp"

namespace gp {

class Player : public Sprite {
public:
	explicit Player(Sprite&& sprite);

	float getVelocity() const;
	void update(float dt);
	void setVelocity(float velocity);
private:
	float m_velocity = 150.0f;
};


inline Player::Player(Sprite&& sprite)
	: Sprite(std::move(sprite))
{

}


inline float Player::getVelocity() const
{
	return m_velocity;
}


inline void Player::update(const float dt)
{
	if (Keyboard::isKeyPressed(GLFW_KEY_D)) {
		setOrigin(getOrigin() + Vec2f(m_velocity * dt, 0));
	} else if (Keyboard::isKeyPressed(GLFW_KEY_A)) {
		setOrigin(getOrigin() - Vec2f(m_velocity * dt, 0));
	}

	if (getRight() > 800.0f)
		setOrigin({getOrigin().x - (getRight() - 800.0f), getOrigin().y});
	else if (getLeft() < 0.0f)
		setOrigin({getOrigin().x - getLeft(), getOrigin().y});
}


inline void Player::setVelocity(const float velocity)
{
	m_velocity = velocity;
}


} // namespace gp
#endif
