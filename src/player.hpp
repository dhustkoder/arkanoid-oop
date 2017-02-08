#ifndef ARKANOID_OOP_PLAYER_HPP_
#define ARKANOID_OOP_PLAYER_HPP_
#include "keyboard.hpp"
#include "sprite.hpp"

namespace gp {

class Player : public Sprite {
public:
	explicit Player(Texture&&) = delete;
	explicit Player(const Texture& texture);

	using Sprite::operator=;
	float getVelocity() const;
	void update(float dt, int maxleft);
	void setVelocity(float velocity);
private:
	float m_velocity = 150.0f;
};


inline Player::Player(const Texture& texture)
	: Sprite(texture)
{

}


inline float Player::getVelocity() const
{
	return m_velocity;
}


inline void Player::update(const float dt, const int maxleft)
{
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		setOrigin(getOrigin() + Vec2f(m_velocity * dt, 0));
	} else if (Keyboard::isKeyPressed(Keyboard::A)) {
		setOrigin(getOrigin() - Vec2f(m_velocity * dt, 0));
	}

	if (getRight() > maxleft)
		setOrigin({getOrigin().x - (getRight() - maxleft), getOrigin().y});
	else if (getLeft() < 0.0f)
		setOrigin({getOrigin().x - getLeft(), getOrigin().y});
}


inline void Player::setVelocity(const float velocity)
{
	m_velocity = velocity;
}


} // namespace gp
#endif

