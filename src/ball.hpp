#ifndef GPROJ_BALL_HPP_
#define GPROJ_BALL_HPP_
#include "keyboard.hpp"
#include "sprite.hpp"
#include "brick.hpp"


namespace gp {

class Ball : public Sprite {
public:
	Ball(const Sprite& sprite);

	void update(const float dt);
	bool intersects(const Sprite& sprite);

	float getRadius() const { return m_radius; }
	const Vec2f& getVelocity() const;

	void setVelocity(const Vec2f& newvelocity);
	
	void setRadius(float radius)
	{
		Sprite::setSize({radius, radius});
		m_radius = radius;
	}

private:
	using Sprite::setSize;
	float m_radius = 0;
	Vec2f m_velocity = { 0, 0 };
};


inline Ball::Ball(const Sprite& sprite)
	: Sprite(sprite)
{
}

inline const Vec2f& gp::Ball::getVelocity() const
{
	return m_velocity;
}


inline void gp::Ball::setVelocity(const Vec2f& newvelocity)
{
	m_velocity = newvelocity;
}


} // namespace gp
#endif
