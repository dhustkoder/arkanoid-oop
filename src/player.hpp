#ifndef ARKANOOP_PLAYER_HPP_
#define ARKANOOP_PLAYER_HPP_
#include "keyboard.hpp"
#include "resource_manager.hpp"

namespace gp {


class Player : public Sprite {
public:
	explicit Player(int max_width, int max_height);
	void update(float dt);
	void reset(int sprite_index);


private:
	SpriteSheet m_sprites;
	int m_maxWidth;
	int m_maxHeight;
};


inline Player::Player(const int max_width, const int max_height) :
	Sprite(ResourceManager::getSpriteSheet("paddles").getTexture()),
	m_sprites(ResourceManager::getSpriteSheet("paddles")),
	m_maxWidth(max_width),
	m_maxHeight(max_height)
{
	
}


inline void Player::update(const float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::D))
		setOrigin(getOrigin() + getVelocity() * dt);
	else if (Keyboard::isKeyPressed(Keyboard::A))
		setOrigin(getOrigin() - getVelocity() * dt);

	if (getRight() > m_maxWidth)
		setOrigin({getOrigin().x - (getRight() - m_maxWidth), getOrigin().y});
	else if (getLeft() < 0.0f)
		setOrigin({getOrigin().x - getLeft(), getOrigin().y});
}


inline void Player::reset(const int sprite_index)
{
	const auto& sprite = m_sprites.getSprite(sprite_index % m_sprites.getSize());
	setSprite(sprite);
	setOrigin({m_maxWidth / 2, m_maxHeight - getHalfSize().y});
	setVelocity({190, 0});
}

} // namespace gp
#endif

