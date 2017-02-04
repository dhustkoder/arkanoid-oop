#ifndef GPROJ_PLAYER_HPP_
#define GPROJ_PLAYER_HPP_
#include "keyboard.hpp"
#include "sprite.hpp"

namespace gp {

class Player : public Sprite {
public:
	Player(const Sprite& sprite);
	Player(const Sprite& sprite, float velocity);
	void update(float dt);

	float getVelocity() const { return m_velocity; }
	void setVelocity(float velocity) { m_velocity = velocity; }

private:
	float m_velocity = 150.0f;
};


inline Player::Player(const Sprite& sprite)
	: Sprite(sprite)
{
}

inline Player::Player(const Sprite& sprite, float velocity)
	: Sprite(sprite),
	m_velocity(velocity)
{

}


inline void Player::update(const float dt)
{
	if (Keyboard::isKeyPressed(GLFW_KEY_D)) {
		setOrigin(getOrigin() + Vec2f(m_velocity * dt, 0));
	} else if (Keyboard::isKeyPressed(GLFW_KEY_A)) {
		setOrigin(getOrigin() - Vec2f(m_velocity * dt, 0));
	}
}



} // namespace gp
#endif
