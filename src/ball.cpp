#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "math_types.hpp"
#include "ball.hpp"


namespace gp {



void Ball::update(const float dt)
{
	if (getRight() >= 800.0f)
		m_velocity.x = -std::abs(m_velocity.x);
	else if (getLeft() <= 0.0f)
		m_velocity.x = std::abs(m_velocity.x);

	if (getBottom() >= 600.0f)
		m_velocity.y = -std::abs(m_velocity.y);
	else if (getTop() <= 0.0f)
		m_velocity.y = std::abs(m_velocity.y);

	setOrigin(getOrigin() + Vec2f(m_velocity * dt));
}


bool Ball::intersects(const Sprite& sprite)
{
	if (getRight() >= sprite.getLeft() &&
	    getLeft() <= sprite.getRight() &&
	    getTop() <= sprite.getBottom() &&
	    getBottom() >= sprite.getTop())
	{
		const Vec2f& ball_center = getOrigin();
		const Vec2f& sprite_center = sprite.getOrigin();
		const Vec2f sprite_size = sprite.getSize();
		
		Vec2f difference = ball_center - sprite_center;
		const Vec2f clamped = glm::clamp(difference, -sprite_size, sprite_size);
		const Vec2f closest = sprite_center + clamped;
		difference = closest - ball_center;
		return glm::length(difference) <= m_radius;
	}

	return false;
}


} // namespace gp
