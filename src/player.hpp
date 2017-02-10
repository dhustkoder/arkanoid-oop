#ifndef ARKANOID_OOP_PLAYER_HPP_
#define ARKANOID_OOP_PLAYER_HPP_
#include "keyboard.hpp"
#include "sprite_sheet.hpp"

namespace gp {


class Player : public Sprite {
public:
	explicit Player(Texture&&) = delete;
	explicit Player(const Texture& texture, int m_winWidth, int m_winHeight);
	void update(float dt);
	void reset(int sprite_index);
private:
	SpriteSheet m_sprites;
	int m_winWidth;
	int m_winHeight;
};


inline Player::Player(const Texture& texture, const int win_width, const int win_height) :
	Sprite(texture),
	m_sprites(texture),
	m_winWidth(win_width),
	m_winHeight(win_height)
{
	m_sprites.mapSprite("blue", {48, 72}, {64, 16});
}


inline void Player::update(const float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::D))
		setOrigin(getOrigin() + getVelocity() * dt);
	else if (Keyboard::isKeyPressed(Keyboard::A))
		setOrigin(getOrigin() - getVelocity() * dt);

	if (getRight() > m_winWidth)
		setOrigin({getOrigin().x - (getRight() - m_winWidth), getOrigin().y});
	else if (getLeft() < 0.0f)
		setOrigin({getOrigin().x - getLeft(), getOrigin().y});
}


inline void Player::reset(const int sprite_index)
{
	const auto& sprite = m_sprites.getSprite(sprite_index % m_sprites.getSize());
	setSprite(sprite);
	setOrigin({m_winWidth / 2, m_winHeight - getHalfSize().y});
	setVelocity({190, 0});
}

} // namespace gp
#endif

