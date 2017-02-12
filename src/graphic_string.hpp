#ifndef ARKANOID_OOP_GRAPHIC_STRING_HPP_
#define ARKANOID_OOP_GRAPHIC_STRING_HPP_
#include <cctype>
#include <vector>
#include "sprite_sheet.hpp"

namespace gp {


class GraphicString {
public:
	GraphicString(std::string str, Vec2f origin,
	              float scale = 1.0f, float spacing = 2.0f,
	              const Vec4f& color = {1, 1, 1, 1});
	~GraphicString();

	const std::vector<Sprite>& getSprites() const;
private:
	std::vector<Sprite> m_spriteString;
	const SpriteSheet& m_spriteSheet;
};


inline const std::vector<Sprite>& GraphicString::getSprites() const
{
	return m_spriteString;
}


} // namespace gp
#endif

