#ifndef ARKANOOP_BALL_HPP_
#define ARKANOOP_BALL_HPP_
#include "keyboard.hpp"
#include "resource_manager.hpp"


namespace gp {


class Ball : public Sprite {
public:
	Ball(int max_width, int max_height);

	float getRadius() const;
	bool isIntersecting(const Sprite& sprite) const;

	void setRadius(float radius);
	void update(float dt);
	void reset(int sprite_index);


private:
	SpriteSheet m_sprites;
	int m_maxWidth;
	int m_maxHeight;
	int m_currentSpriteIndex;
	float m_radius;
};


inline Ball::Ball(const int max_width, const int max_height) :
	Sprite(ResourceManager::getSpriteSheet("balls").getTexture()),
	m_sprites(ResourceManager::getSpriteSheet("balls")),
	m_maxWidth(max_width),
	m_maxHeight(max_height),
	m_currentSpriteIndex(0),
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



inline void Ball::update(const float dt)
{
	if (getRight() > m_maxWidth) {
		setOrigin({m_maxWidth - getHalfSize().x, getOrigin().y});
		setVelocity({-std::abs(getVelocity().x), getVelocity().y});
	} else if (getLeft() < 0) {
		setOrigin({getHalfSize().x, getOrigin().y});
		setVelocity({std::abs(getVelocity().x), getVelocity().y});
	}

	if (getBottom() > m_maxHeight) {
		setOrigin({getOrigin().x, m_maxHeight - getHalfSize().y});
		setVelocity({getVelocity().x, -std::abs(getVelocity().y)});
		reset(++m_currentSpriteIndex);
		
		if (m_currentSpriteIndex >= m_sprites.getSize())
			m_currentSpriteIndex = 0;

	} else if (getTop() < 0) {
		setOrigin({getOrigin().x, getHalfSize().y});
		setVelocity({getVelocity().x, std::abs(getVelocity().y)});
	}

	setOrigin(getOrigin() +  getVelocity() * dt);
}


inline bool Ball::isIntersecting(const Sprite& brick) const
{
	if (checkAABBCollision(brick)) {
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


inline void Ball::reset(const int sprite_index)
{
	const Vec2f default_origin { m_maxWidth / 2, m_maxHeight / 2};
	const Vec2f default_velocity { 200, 200 };
	const float default_radius = 8.0f;

	setSprite(m_sprites.getSprite(sprite_index % m_sprites.getSize()));
	setOrigin(default_origin);
	setVelocity(default_velocity);
	setRadius(default_radius);
}


} // namespace gp
#endif

