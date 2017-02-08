#ifndef ARKANOID_OOP_BALL_HPP_
#define ARKANOID_OOP_BALL_HPP_
#include "keyboard.hpp"
#include "sprite.hpp"
#include "brick.hpp"


namespace gp {


class Ball : public Sprite {
public:
	Ball(Texture&&) = delete;
	Ball(const Texture& texture);

	void update(float dt, int maxleft, int maxbottom);
	bool isIntersecting(const Sprite& sprite);

	float getRadius() const;
	void setRadius(float radius);

private:
	float m_radius;
};


inline Ball::Ball(const Texture& texture)
	: Sprite(texture),
	m_radius(0)
{
}


inline float Ball::getRadius() const
{
	return m_radius;
}



inline void Ball::setRadius(const float radius)
{
	setSize({radius * 2.0f, radius * 2.0f});
	m_radius = radius;
}



inline void Ball::update(const float dt, const int maxleft, const int maxbottom)
{
	if (getRight() > maxleft) {
		setOrigin({maxleft - getHalfSize().x, getOrigin().y});
		setVelocity({-std::abs(getVelocity().x), getVelocity().y});
	} else if (getLeft() < 0) {
		setOrigin({getHalfSize().x, getOrigin().y});
		setVelocity({std::abs(getVelocity().x), getVelocity().y});
	}

	if (getBottom() > maxbottom) {
		setOrigin({getOrigin().x, maxbottom - getHalfSize().y});
		setVelocity({getVelocity().x, -std::abs(getVelocity().y)});
	} else if (getTop() < 0) {
		setOrigin({getOrigin().x, getHalfSize().y});
		setVelocity({getVelocity().x, std::abs(getVelocity().y)});
	}

	setOrigin(getOrigin() +  getVelocity() * dt);
}


inline bool Ball::isIntersecting(const Sprite& brick)
{
	if (checkAABBCollision(brick))
	{
		const Vec2f& ball_origin = getOrigin();
		const Vec2f& aabb_origin = brick.getOrigin();
		const Vec2f aabb_half_size = brick.getHalfSize();
		
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
