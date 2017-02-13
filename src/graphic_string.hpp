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

	GraphicString(std::string str, Vec2f pos = {0, 0},
	              float scale = 1.0f, float spacing = 2.0f,
	              const Vec4f& color = {1, 1, 1, 1});
	GraphicString();

	const std::string& getString() const;
	const Vec2f& getPos() const;
	float getTop() const;
	float getBottom() const;
	float getRight() const;
	float getLeft() const;
	float getScale() const;
	float getSpacing() const;
	const Vec4f& getColor() const;



	void setString(std::string str);
	void setPos(const Vec2f& origin);
	void setScale(float scale);
	void setSpacing(float spacing);
	void setColor(const Vec4f& color);

	~GraphicString();

	const std::vector<Sprite>& getSprites() const;
private:
	void evaluateSpriteString();

	std::vector<Sprite> m_spriteString;
	std::string m_str;
	Vec2f m_pos;
	float m_top;
	float m_bottom;
	float m_right;
	float m_left;
	float m_scale;
	float m_spacing;
	Vec4f m_color;
	const SpriteSheet* m_spriteSheet;
};


inline GraphicString::GraphicString()
	: GraphicString("")
{

}


inline const std::string& GraphicString::getString() const
{
	return m_str;
}


inline float GraphicString::getScale() const
{
	return m_scale;
}


inline float GraphicString::getSpacing() const
{
	return m_spacing;
}


inline const Vec2f& GraphicString::getPos() const
{
	return m_pos;
}


inline float GraphicString::getTop() const
{
	return m_top;
}


inline float GraphicString::getBottom() const
{
	return m_bottom;
}


inline float GraphicString::getRight() const
{
	return m_right;
}


inline float GraphicString::getLeft() const
{
	return m_left;
}


inline const Vec4f& GraphicString::getColor() const
{
	return m_color;
}


inline void GraphicString::setString(std::string str)
{
	m_str = std::move(str);
	evaluateSpriteString();
}


inline void GraphicString::setPos(const Vec2f& pos)
{
	m_pos = pos;
	evaluateSpriteString();
}


inline void GraphicString::setScale(const float scale)
{
	m_scale = scale;
	evaluateSpriteString();
}


inline void GraphicString::setSpacing(const float spacing)
{
	m_spacing = spacing;
	evaluateSpriteString();
}


inline void GraphicString::setColor(const Vec4f& color)
{
	m_color = color;
	evaluateSpriteString();
}


inline const std::vector<Sprite>& GraphicString::getSprites() const
{
	return m_spriteString;
}


} // namespace gp
#endif

