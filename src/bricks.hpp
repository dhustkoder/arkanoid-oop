#ifndef ARKANOID_OOP_BRICKS_HPP_
#define ARKANOID_OOP_BRICKS_HPP_
#include "brick.hpp"
#include "sprite_sheet.hpp"


namespace gp {


class Bricks {
public:
	Bricks(Texture&&) = delete;

	Bricks(const Texture& texture, int win_width, int win_heigth);
	const std::vector<Brick>& getBricks() const;
	std::vector<Brick>& getBricks();

	void update(float dt);
	void reset(int num_lines);
private:
	void removeDestroyedBricks();

	SpriteSheet m_sprites;
	std::vector<Brick> m_bricks;
	int m_destroyedBricks;
	int m_winWidth;
	int m_winHeight;
};


inline Bricks::Bricks(const Texture& texture, int win_width, int win_height)
	: m_sprites(texture),
	m_destroyedBricks(0),
	m_winWidth(win_width),
	m_winHeight(win_height)

{
	m_sprites.mapSprite("blue_brick", {8, 8}, {32, 16});
	m_sprites.mapSprite("blue_green_brick", {48, 8}, {32, 16});
	m_sprites.mapSprite("blue_red_brick", {84, 8}, {32, 16});
	m_sprites.mapSprite("blue_purple_brick", {120, 8}, {32, 16});
	m_sprites.mapSprite("blue_yellow_brick", {156, 8}, {32, 16});
	m_sprites.mapSprite("blue_black_brick", {192, 8}, {32, 16});
	m_sprites.mapSprite("blue_darkyellow_brick", {228, 8}, {32, 16});
	m_sprites.mapSprite("yellow_purple_brick", {264, 8}, {32, 16});
	m_sprites.mapSprite("green_brick", {8, 28}, {32, 16});
	m_sprites.mapSprite("green_red_brick", {48, 28}, {32, 16});
	m_sprites.mapSprite("green_purple_brick", {84, 28}, {32, 16});
	m_sprites.mapSprite("green_yellow_brick", {120, 28}, {32, 16});
	m_sprites.mapSprite("green_dark_brick", {156, 28}, {32, 16});
	m_sprites.mapSprite("green_darkyellow_brick", {192, 28}, {32, 16});
	m_sprites.mapSprite("dark_darkyellow_brick", {228, 28}, {32, 16});
	m_sprites.mapSprite("dark_purple_brick", {264, 28}, {32, 16});
}


inline const std::vector<Brick>& Bricks::getBricks() const
{
	return m_bricks;
}


inline std::vector<Brick>& Bricks::getBricks()
{
	return m_bricks;
}


inline void Bricks::update(float /*dt*/)
{
}


inline void Bricks::reset(const int num_lines)
{
	const Vec2f sprite_size = m_sprites.getSprite(0).getSize();
	Vec2f origin { (sprite_size.x + 8) / 2.0f, (sprite_size.y + 8) / 2.0f };

	const int brick_count = num_lines * (m_winWidth / static_cast<int>(sprite_size.x + 8));

	m_bricks.reserve(brick_count);

	for (int i = 0; i < brick_count; ++i) {
		const Sprite& sprite = m_sprites.getSprite(i % m_sprites.getSize());
		m_bricks.emplace_back(sprite.getTexture());
		m_bricks.back().setSprite(sprite);
		m_bricks.back().setOrigin(origin);
		m_bricks.back().setSize(sprite_size);

		origin.x += sprite_size.x + 8;
		if (origin.x > (m_winWidth - ((sprite_size.x + 8) / 2.0f))) {
			origin.x = (sprite_size.x + 8) / 2.0f;
			origin.y += sprite_size.y + 8;
			if (origin.y > (m_winWidth - ((sprite_size.y + 8) / 2.0f)))
				origin.y = (sprite_size.y + 8) / 2.0f;
		}
	}
}


inline void Bricks::removeDestroyedBricks()
{
	const auto is_destroyed = [](const Brick& brick) {
		return brick.isDestroyed();
	};

	m_bricks.erase(std::remove_if(m_bricks.begin(), m_bricks.end(), is_destroyed), m_bricks.end());
}


}
#endif

