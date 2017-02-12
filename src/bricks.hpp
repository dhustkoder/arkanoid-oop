#ifndef ARKANOOP_BRICKS_HPP_
#define ARKANOOP_BRICKS_HPP_
#include "brick.hpp"
#include "resource_manager.hpp"


namespace gp {


class Bricks {
public:
	Bricks(int max_width, int max_heigth);
	const std::vector<Brick>& getBricks() const;
	int getDestroyedBricksCount() const;
	std::vector<Brick>& getBricks();

	void update(float dt);
	void reset(int num_lines);

private:
	void removeDestroyedBricks();

	SpriteSheet m_sprites;
	std::vector<Brick> m_bricks;
	int m_destroyedBricks;
	int m_maxWidth;
	int m_maxHeight;
};


inline Bricks::Bricks(int max_width, int max_height)
	: m_sprites(ResourceManager::getSpriteSheet("bricks")),
	m_destroyedBricks(0),
	m_maxWidth(max_width),
	m_maxHeight(max_height)

{
}


inline const std::vector<Brick>& Bricks::getBricks() const
{
	return m_bricks;
}


inline std::vector<Brick>& Bricks::getBricks()
{
	return m_bricks;
}


inline int Bricks::getDestroyedBricksCount() const
{
	return m_destroyedBricks;
}


inline void Bricks::update(float /*dt*/)
{
}


inline void Bricks::reset(const int num_lines)
{
	const Vec2f sprite_size = m_sprites.getSprite(0).getSize();
	Vec2f origin { (sprite_size.x + 8) / 2.0f, (sprite_size.y + 8) / 2.0f };

	const int brick_count = num_lines * (m_maxWidth / static_cast<int>(sprite_size.x + 8));

	m_bricks.reserve(brick_count);

	for (int i = 0; i < brick_count; ++i) {
		const Sprite& sprite = m_sprites.getSprite(i % m_sprites.getSize());
		m_bricks.emplace_back(sprite.getTexture());
		m_bricks.back().setSprite(sprite);
		m_bricks.back().setOrigin(origin);
		m_bricks.back().setSize(sprite_size);

		origin.x += sprite_size.x + 8;
		if (origin.x > (m_maxWidth - ((sprite_size.x + 8) / 2.0f))) {
			origin.x = (sprite_size.x + 8) / 2.0f;
			origin.y += sprite_size.y + 8;
			if (origin.y > (m_maxHeight - ((sprite_size.y + 8) / 2.0f)))
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

