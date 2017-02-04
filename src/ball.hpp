#ifndef GPROJ_BALL_HPP_
#define GPROJ_BALL_HPP_
#include "keyboard.hpp"
#include "sprite.hpp"


namespace gp {

class Ball : public Sprite {
public:
	Ball(const Texture& texture,
	     const Vec2f& pos,
	     float radius,
	     float velocity,
	     const Vec2f& uv_pos,
	     const Vec2f& uv_size);

	void update(const float dt);

private:
	float m_velocity;
};


Ball::Ball(const Texture& texture, const Vec2f& pos,
	float radius, float velocity,
	const Vec2f& uv_pos, const Vec2f& uv_size)
	: Sprite(texture, pos, {radius / 2.0f, radius / 2.0f} , uv_pos, uv_size),
	m_velocity(velocity)
{

}


void Ball::update(const float dt)
{
	if (Keyboard::isKeyPressed(GLFW_KEY_W)) {
		this->setPosition(this->getPosition() - Vec2f(0, m_velocity * dt));
	} else if (Keyboard::isKeyPressed(GLFW_KEY_S)) {
		this->setPosition(this->getPosition() + Vec2f(0, m_velocity * dt));
	}

	if (Keyboard::isKeyPressed(GLFW_KEY_D)) {
		this->setPosition(this->getPosition() + Vec2f(m_velocity * dt, 0));
	} else if (Keyboard::isKeyPressed(GLFW_KEY_A)) {
		this->setPosition(this->getPosition() - Vec2f(m_velocity * dt, 0));
	}
}

} // namespace gp

#endif