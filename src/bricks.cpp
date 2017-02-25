#include "display.hpp"
#include "bricks.hpp"
#include "resource_manager.hpp"


namespace gp {


Brick::Brick(int resistence)
	: Sprite(ResourceManager::getSpriteSheet("bricks").getTexture()),
	m_resistence(resistence)
{
}


void Bricks::reset(const int num_lines)
{
	const SpriteSheet& sprites = ResourceManager::getSpriteSheet("bricks");

	const Vec2f sprite_size = sprites.getSprite(0).getSize();
	Vec2f origin { (sprite_size.x + 8) / 2.0f, (sprite_size.y + 8) / 2.0f };

	const int brick_count = num_lines * (static_cast<int>(Display::getViewSize().x) /
	                                     static_cast<int>(sprite_size.x + 8));

	m_bricks.reserve(brick_count);

	for (int i = 0; i < brick_count; ++i) {
		const Sprite& sprite = sprites.getSprite(i % sprites.getSize());
		m_bricks.emplace_back(Brick(i % 3));
		m_bricks.back().setSprite(sprite);
		m_bricks.back().setOrigin(origin);
		m_bricks.back().setSize(sprite_size);

		origin.x += sprite_size.x + 8;
		if (origin.x > (Display::getViewSize().x - ((sprite_size.x + 8) / 2.0f))) {
			origin.x = (sprite_size.x + 8) / 2.0f;
			origin.y += sprite_size.y + 8;
			if (origin.y > (Display::getViewSize().y - ((sprite_size.y + 8) / 2.0f)))
				origin.y = (sprite_size.y + 8) / 2.0f;
		}
	}
}

} // namespace gp
