#include "resource_manager.hpp"
#include "graphic_string.hpp"


namespace gp {


GraphicString::GraphicString(std::string str, Vec2f pos, const float scale,
                             const float spacing, const Vec4f& color)

	: m_str(std::move(str)),
	m_pos(pos),
	m_scale(scale),
	m_spacing(spacing),
	m_color(color),
	m_spriteSheet(&ResourceManager::getSpriteSheet("fontset"))
{
	evaluateSpriteString();
}


GraphicString::~GraphicString()
{

}


void GraphicString::evaluateSpriteString()
{
	m_spriteString.clear();

	if (m_str.empty()) {
		m_top = -1;
		m_bottom = -1;
		m_right = -1;
		m_left = -1;
		return;
	}

	m_spriteString.reserve(m_str.size());


	GLfloat previus_right = -1;
	Vec2f pos = m_pos;

	for (std::string::size_type i = 0; i < m_str.size(); ++i) {

		if (m_str[i] == '\n') {
			pos.y += m_spriteString.back().getSize().y + m_spacing;
			pos.x = m_pos.x;
			previus_right = -1;
			continue;
		}

		Sprite sprite = m_spriteSheet->getSprite(m_str.substr(i, 1));
		sprite.setSize(sprite.getSize() * m_scale);
		sprite.setColor(m_color);
		sprite.setOrigin(pos + sprite.getHalfSize());

		if (!m_spriteString.empty()) {
			const GLfloat current_left = sprite.getLeft();
			if (previus_right >= current_left) {
				pos.x += (previus_right - current_left) + m_spacing;
				sprite.setOrigin(pos + sprite.getHalfSize());
			}
		}

		previus_right = sprite.getRight();
		if (m_str[i] != ' ')
			m_spriteString.emplace_back(std::move(sprite));
	}
	
	m_right = std::max_element(m_spriteString.cbegin(), m_spriteString.cend(),
	                           [](const Sprite& s1, const Sprite& s2) {
	                           	return s1.getRight() < s2.getRight();
	                           })->getRight();

	m_top = m_spriteString.front().getTop();
	m_left = m_spriteString.front().getLeft();
	m_bottom = m_spriteString.back().getBottom();

}


} // namespace gp

