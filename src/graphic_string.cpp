#include "resource_manager.hpp"
#include "graphic_string.hpp"


namespace gp {


GraphicString::GraphicString(std::string str, Vec2f origin, const float scale,
                             const float spacing, const Vec4f& color)

	: m_spriteSheet(ResourceManager::getSpriteSheet("alpha_numeric"))

{
	if (str.empty())
		return;

	m_spriteString.reserve(str.size());

	for (std::string::size_type i = 0; i < str.size(); ++i) {
		str[i] = std::toupper(str[i]);
		m_spriteString.emplace_back(m_spriteSheet.getSprite(str.substr(i, 1)));
		m_spriteString.back().setOrigin(origin);
		m_spriteString.back().setSize(m_spriteString.back().getSize() * scale);
		m_spriteString.back().setColor(color);

		if (m_spriteString.size() > 1) {
			const GLfloat previus_right = (m_spriteString.end() - 2)->getRight();
			const GLfloat current_left = (m_spriteString.end() - 1)->getLeft();
			if (previus_right >= current_left) {
				origin.x += (previus_right - current_left) + spacing;
				m_spriteString.back().setOrigin(origin);
			}
		}
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
