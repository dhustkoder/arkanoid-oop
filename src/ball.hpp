#ifndef ARKANOID_OOP_BALL_HPP_
#define ARKANOID_OOP_BALL_HPP_
#include "keyboard.hpp"
#include "sprite.hpp"
#include "brick.hpp"


namespace gp {


class Ball : public Sprite {
public:
	explicit Ball(const Sprite& sprite);

	void update(const float dt);
	bool intersects(const Sprite& sprite, Vec2f* difference);

	float getRadius() const;
	const Vec2f& getVelocity() const;

	void setRadius(float radius);
	void setVelocity(const Vec2f& newvelocity);
private:
	using Sprite::setSize;
	using Sprite::getSize;
	float m_radius = 0;
	Vec2f m_velocity = { 0, 0 };
};


inline Ball::Ball(const Sprite& sprite)
	: Sprite(sprite)
{
}


inline float Ball::getRadius() const
{
	return m_radius;
}


inline const Vec2f& gp::Ball::getVelocity() const
{
	return m_velocity;
}


inline void Ball::setRadius(const float radius)
{
	Sprite::setSize({radius * 2.0f, radius * 2.0f});
	m_radius = radius;
}


inline void gp::Ball::setVelocity(const Vec2f& newvelocity)
{
	m_velocity = newvelocity;
}


inline void Ball::update(const float dt)
{
	/*
	if (getRight() >= 800.0f)
		m_velocity.x = -std::abs(m_velocity.x);
	else if (getLeft() <= 0.0f)
		m_velocity.x = std::abs(m_velocity.x);

	if (getBottom() >= 600.0f)
		m_velocity.y = -std::abs(m_velocity.y);
	else if (getTop() <= 0.0f)
		m_velocity.y = std::abs(m_velocity.y);

	setOrigin(getOrigin() + Vec2f(m_velocity * dt));
	*/

	if (Keyboard::isKeyPressed(GLFW_KEY_W))
		setOrigin(getOrigin() - Vec2f(0, m_velocity.y * dt));
	else if (Keyboard::isKeyPressed(GLFW_KEY_S))
		setOrigin(getOrigin() + Vec2f(0, m_velocity.y * dt));

	if (Keyboard::isKeyPressed(GLFW_KEY_D))
		setOrigin(getOrigin() + Vec2f(m_velocity.x * dt, 0));
	else if (Keyboard::isKeyPressed(GLFW_KEY_A))
		setOrigin(getOrigin() - Vec2f(m_velocity.y * dt, 0));
}


inline bool Ball::intersects(const Sprite& sprite, Vec2f* const difference)
{
	if (getRight() >= sprite.getLeft() &&
	    getLeft() <= sprite.getRight() &&
	    getTop() <= sprite.getBottom() &&
	    getBottom() >= sprite.getTop())
	{
		const Vec2f& ball_origin = getOrigin();
		const Vec2f& sprite_origin = sprite.getOrigin();
		const Vec2f sprite_size = sprite.getSize();
		
		Vec2f diff = ball_origin - sprite_origin;
		const Vec2f clamped = glm::clamp(diff, -sprite_size, sprite_size);
		const Vec2f closest = sprite_origin + clamped;
		diff = closest - ball_origin;

		if (glm::length(diff) <= m_radius) {
			*difference = diff;
			return true;
		}
	}

	return false;
}


} // namespace gp
#endif
