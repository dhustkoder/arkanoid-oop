#ifndef ARKANOOP_GRAPHIC_STRING_HPP_
#define ARKANOOP_GRAPHIC_STRING_HPP_
#include <cctype>
#include <vector>
#include "sprite_sheet.hpp"

namespace gp {


class GraphicString {
public:
	GraphicString& operator=(GraphicString&& other) noexcept = default;
	GraphicString(GraphicString&& other) noexcept = default;

	GraphicString(std::string str, Vec2f origin = {0, 0},
	              float scale = 1.0f, float spacing = 2.0f,
	              const Vec4f& color = {1, 1, 1, 1});
	GraphicString();

	void setString(std::string str);
	void setOrigin(const Vec2f& origin);
	void setScale(float scale);
	void setSpacing(float spacing);
	void setColor(const Vec4f& color);

	~GraphicString();

	const std::vector<Sprite>& getSprites() const;
private:
	std::vector<Sprite> m_spriteString;
	std::string m_str;
	float m_scale;
	float m_spacing;
	Vec2f m_origin;
	Vec4f m_color;
	const SpriteSheet* m_spriteSheet;
};


inline GraphicString::GraphicString()
	: GraphicString("")
{

}


inline void GraphicString::setString(std::string str)
{
	*this = GraphicString(std::move(str), m_origin, m_scale, m_spacing, m_color);
}


inline void GraphicString::setOrigin(const Vec2f& origin)
{
	*this = GraphicString(std::move(m_str), origin, m_scale, m_spacing, m_color);
}


inline void GraphicString::setScale(const float scale)
{
	*this = GraphicString(std::move(m_str), m_origin, scale, m_spacing, m_color);
}


inline void GraphicString::setSpacing(const float spacing)
{
	*this = GraphicString(std::move(m_str), m_origin, m_scale, spacing, m_color);
}


inline void GraphicString::setColor(const Vec4f& color)
{
	*this = GraphicString(std::move(m_str), m_origin, m_scale, m_spacing, color);
}

inline const std::vector<Sprite>& GraphicString::getSprites() const
{
	return m_spriteString;
}


} // namespace gp
#endif

