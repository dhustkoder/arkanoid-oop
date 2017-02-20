#ifndef ARKANOOP_PLAYER_HPP_
#define ARKANOOP_PLAYER_HPP_
#include "display.hpp"
#include "keyboard.hpp"
#include "resource_manager.hpp"

namespace gp {


class Player : public Sprite {
public:
	explicit Player();
	void update(float dt);
	void reset(int sprite_index);


private:
	SpriteSheet m_sprites;
};


inline Player::Player() :
	Sprite(ResourceManager::getSpriteSheet("paddles").getTexture()),
	m_sprites(ResourceManager::getSpriteSheet("paddles"))
{
	
}


inline void Player::update(const float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::D))
		setOrigin(getOrigin() + getVelocity() * dt);
	else if (Keyboard::isKeyPressed(Keyboard::A))
		setOrigin(getOrigin() - getVelocity() * dt);

	if (getRight() > Display::getViewSize().x)
		setOrigin({getOrigin().x - (getRight() - Display::getViewSize().x), getOrigin().y});
	else if (getLeft() < 0.0f)
		setOrigin({getOrigin().x - getLeft(), getOrigin().y});
}


inline void Player::reset(const int sprite_index)
{
	const auto& sprite = m_sprites.getSprite(sprite_index % m_sprites.getSize());
	setSprite(sprite);
	setOrigin({Display::getViewSize().x / 2, Display::getViewSize().y - getHalfSize().y});
	setVelocity({190, 0});
}

} // namespace gp
#endif

