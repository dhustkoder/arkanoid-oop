#ifndef ARKANOID_OOP_BALL_HPP_
#define ARKANOID_OOP_BALL_HPP_
#include "keyboard.hpp"
#include "sprite.hpp"
#include "brick.hpp"


namespace gp {


class Ball : public Sprite {
public:
	explicit Ball(Texture&&) = delete;
	explicit Ball(const Texture& texture);

	void update(const float dt, int maxleft, int maxbottom);
	bool isIntersecting(const Sprite& sprite);

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


inline Ball::Ball(const Texture& texture)
	: Sprite(texture)
{

}


inline float Ball::getRadius() const
{
	return m_radius;
}


inline const Vec2f& Ball::getVelocity() const
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


inline void Ball::update(const float dt, const int maxleft, const int maxbottom)
{
	if (getRight() >= maxleft)
		m_velocity.x = -std::abs(m_velocity.x);
	else if (getLeft() <= 0.0f)
		m_velocity.x = std::abs(m_velocity.x);

	if (getBottom() >= maxbottom)
		m_velocity.y = -std::abs(m_velocity.y);
	else if (getTop() <= 0.0f)
		m_velocity.y = std::abs(m_velocity.y);

	setOrigin(getOrigin() + Vec2f(m_velocity * dt));
/*

	if (Keyboard::isKeyPressed(GLFW_KEY_W))
		setOrigin(getOrigin() - Vec2f(0, m_velocity.y * dt));
	else if (Keyboard::isKeyPressed(GLFW_KEY_S))
		setOrigin(getOrigin() + Vec2f(0, m_velocity.y * dt));

	if (Keyboard::isKeyPressed(GLFW_KEY_D))
		setOrigin(getOrigin() + Vec2f(m_velocity.x * dt, 0));
	else if (Keyboard::isKeyPressed(GLFW_KEY_A))
		setOrigin(getOrigin() - Vec2f(m_velocity.y * dt, 0));
*/
}


inline bool Ball::isIntersecting(const Sprite& sprite)
{
	if (getRight() >= sprite.getLeft() &&
	    getLeft() <= sprite.getRight() &&
	    getTop() <= sprite.getBottom() &&
	    getBottom() >= sprite.getTop())
	{
		const Vec2f& ball_origin = getOrigin();
		const Vec2f& aabb_origin = sprite.getOrigin();
		const Vec2f aabb_half_size = sprite.getHalfSize();
		
		const Vec2f aabb_origin_to_ball_origin_diff = ball_origin - aabb_origin;
		const Vec2f closest =
		  aabb_origin + glm::clamp(aabb_origin_to_ball_origin_diff,
		                           -aabb_half_size,
			                    aabb_half_size);

		const Vec2f closest_to_ball_origin_diff = closest - ball_origin;

		return glm::length(closest_to_ball_origin_diff) < m_radius;
	}

	return false;
}


} // namespace gp
#endif
