#include "resource_manager.hpp"
#include "graphic_string.hpp"


namespace gp {


GraphicString::GraphicString(std::string str, Vec2f origin, const float scale,
                             const float spacing, const Vec4f& color)

	: m_str(std::move(str)),
	m_scale(scale),
	m_spacing(spacing),
	m_origin(origin),
	m_color(color),
	m_spriteSheet(&ResourceManager::getSpriteSheet("fontset"))
{
	if (m_str.empty())
		return;

	m_spriteString.reserve(m_str.size());

	GLfloat previus_right = 0.0f;

	for (std::string::size_type i = 0; i < m_str.size(); ++i) {
		m_str[i] = std::toupper(m_str[i]);

		Sprite sprite = m_spriteSheet->getSprite(m_str.substr(i, 1));
		sprite.setOrigin(origin);
		sprite.setSize(sprite.getSize() * m_scale);
		sprite.setColor(m_color);

		if (!m_spriteString.empty()) {
			const GLfloat current_left = sprite.getLeft();
			if (previus_right >= current_left) {
				origin.x += (previus_right - current_left) + m_spacing;
				sprite.setOrigin(origin);
			}
		}

		previus_right = sprite.getRight();
		if (m_str[i] != ' ')
			m_spriteString.emplace_back(std::move(sprite));
	}

	
	// find the common middle point in the string
	// and move the string to the left to fit the origin
	
	const GLfloat right = m_spriteString.back().getRight();
	const GLfloat left = m_spriteString.front().getLeft();
	const GLfloat middle = (right - left) / 2.0f;

	for (auto& sprite : m_spriteString)
		sprite.setOrigin({sprite.getOrigin().x - middle, sprite.getOrigin().y});
}


GraphicString::~GraphicString()
{

}


} // namespace gp
