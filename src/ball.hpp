#ifndef ARKANOOP_BALL_HPP_
#define ARKANOOP_BALL_HPP_
#include "keyboard.hpp"
#include "player.hpp"


namespace gp {


class Ball : public Sprite {
public:
	static constexpr const float kDefaultVelocity = 150.0f;

	Ball();

	float getRadius() const;
	bool isIntersecting(const Sprite& sprite) const;
	bool isStuckIntoPlayer() const;

	void setRadius(float radius);
	void update(float dt);
	void reset(int sprite_index);
	void stuckIntoPlayer(const Player& player);
private:
	const Player* m_player;
	int m_currentSpriteIndex;
	float m_radius;
	bool m_isStuck;
};


inline Ball::Ball() :
	Sprite(ResourceManager::getSpriteSheet("balls").getTexture()),
	m_player(nullptr),
	m_currentSpriteIndex(0),
	m_radius(0),
	m_isStuck(false)
{

}


inline float Ball::getRadius() const
{
	return m_radius;
}


inline bool Ball::isStuckIntoPlayer() const
{
	return m_isStuck;
}


inline void Ball::setRadius(const float radius)
{
	setSize({radius * 2.0f, radius * 2.0f});
	m_radius = radius;
}



inline void Ball::update(const float dt)
{
	if (m_isStuck) {

		setOrigin({m_player->getOrigin().x,
		           m_player->getOrigin().y -
			   m_player->getHalfSize().y -
		           getHalfSize().y});

		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			
			float xmul;

			if (Keyboard::isKeyPressed(Keyboard::A))
				xmul = -1;
			else if (Keyboard::isKeyPressed(Keyboard::D))
				xmul = 1;
			else
				xmul = 0;

			setVelocity({kDefaultVelocity * xmul, -kDefaultVelocity});

			m_isStuck = false;
			m_player = nullptr;
		}

		return;
	}


	if (getRight() > Display::getViewSize().x) {
		setOrigin({Display::getViewSize().x - getHalfSize().x, getOrigin().y});
		setVelocity({-std::abs(getVelocity().x), getVelocity().y});
	} else if (getLeft() < 0) {
		setOrigin({getHalfSize().x, getOrigin().y});
		setVelocity({std::abs(getVelocity().x), getVelocity().y});
	}

	if (getBottom() > Display::getViewSize().y) {
		setOrigin({getOrigin().x, Display::getViewSize().y - getHalfSize().y});
		setVelocity({getVelocity().x, -std::abs(getVelocity().y)});
		reset(++m_currentSpriteIndex);
	
		const SpriteSheet& sprites = ResourceManager::getSpriteSheet("balls");	
		if (m_currentSpriteIndex >= sprites.getSize())
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
	const float default_radius = 8.0f;
	const SpriteSheet& sprites = ResourceManager::getSpriteSheet("balls");
	setSprite(sprites.getSprite(sprite_index % sprites.getSize()));
	setRadius(default_radius);
}


inline void Ball::stuckIntoPlayer(const Player& player)
{
	m_player = &player;

	setOrigin({m_player->getOrigin().x,
	           m_player->getOrigin().y -
	           m_player->getHalfSize().y -
	           getHalfSize().y});

	m_isStuck = true;
}


} // namespace gp
#endif

