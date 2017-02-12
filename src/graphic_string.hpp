#ifndef ARKANOID_OOP_GRAPHIC_STRING_HPP_
#define ARKANOID_OOP_GRAPHIC_STRING_HPP_
#include <cctype>
#include <vector>
#include "sprite_sheet.hpp"

namespace gp {


class GraphicString {
public:
	GraphicString(std::string str, Vec2f origin, const SpriteSheet& letters,
	              float scale = 2.0f, float spacing = 2.0f, const Vec4f& color = {1, 1, 1, 1});

	const std::vector<Sprite>& getSprites() const;
private:
	std::vector<Sprite> m_spriteString;
	const SpriteSheet& m_letters;
};


inline GraphicString::GraphicString(std::string str, Vec2f origin, const SpriteSheet& letters,
                                    const float scale, const float spacing, const Vec4f& color)
	: m_letters(letters)

{
	if (str.empty())
		return;

	m_spriteString.reserve(str.size());

	for (std::string::size_type i = 0; i < str.size(); ++i) {
	
		if (str[i] != ' ') {
			str[i] = std::toupper(str[i]);
			m_spriteString.emplace_back(m_letters.getSprite(str.substr(i, 1)));
			m_spriteString.back().setOrigin(origin);
			m_spriteString.back().setSize(m_spriteString.back().getSize() * scale);
			m_spriteString.back().setColor(color);
			origin.x += m_spriteString.back().getSize().x + spacing;
			continue;
		}

		origin.x += spacing * 2.0f;
	}

	
	// find the common middle point in the string
	// and move the string to the left to fit the origin
	
	const GLfloat right = m_spriteString.back().getRight();
	const GLfloat left = m_spriteString.front().getLeft();
	const GLfloat middle = (right - left) / 2.0f;

	for (auto& sprite : m_spriteString)
		sprite.setOrigin({sprite.getOrigin().x - middle, sprite.getOrigin().y});
}


inline const std::vector<Sprite>& GraphicString::getSprites() const
{
	return m_spriteString;
}


}
#endif

