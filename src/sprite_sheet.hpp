#ifndef ARKANOID_OOP_SPRITE_SHEET_HPP_
#define ARKANOID_OOP_SPRITE_SHEET_HPP_
#include <cctype>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

#include "exception.hpp"
#include "math_types.hpp"
#include "texture.hpp"
#include "sprite.hpp"


namespace gp {


class SpriteSheet {
	using SpriteMap = std::vector<std::pair<std::string, Sprite>>;
public:
	SpriteSheet(const Texture& texture);

	const Sprite& getSprite(const std::string& name) const;
	const Sprite& getSprite(const int index) const;
	const Texture& getTexture() const;
	int getSize() const;

	void mapSprite(std::string name, const Vec2f& uv_pos, const Vec2f& uv_size);

private:
	SpriteMap::const_iterator find(const std::string& name) const;
	SpriteMap::iterator find(const std::string& name);


	const Texture& m_texture;
	SpriteMap m_sprites;
};


inline SpriteSheet::SpriteSheet(const Texture& texture)
	: m_texture(texture)
{

}


inline const Sprite& SpriteSheet::getSprite(const std::string& name) const
{		
	const auto itr = find(name);
	if (itr == m_sprites.end())
		throw Exception("request for unmapped sprite: " + name);

	return itr->second;
}


inline const Sprite& SpriteSheet::getSprite(const int index) const
{
	return m_sprites.at(index).second;
}


inline const Texture& SpriteSheet::getTexture() const
{
	return m_texture;
}


inline int SpriteSheet::getSize() const
{
	return static_cast<int>(m_sprites.size());
}


inline void SpriteSheet::mapSprite(std::string name, const Vec2f& uv_pos, const Vec2f& uv_size)
{
	for (auto& c : name)
		c = std::toupper(c);

	const auto itr = find(name);
	if (itr == m_sprites.end())
		m_sprites.emplace_back(std::move(name), Sprite(m_texture, {0, 0}, uv_size, uv_pos, uv_size));
	else
		itr->second = Sprite(m_texture, {0, 0}, uv_size, uv_pos, uv_size);
}




inline SpriteSheet::SpriteMap::const_iterator SpriteSheet::find(const std::string& name) const
{
	return std::find_if(m_sprites.cbegin(), m_sprites.cend(),
		[&] (const std::pair<std::string, Sprite>& pair) {
			return pair.first == name;
		});
}


inline SpriteSheet::SpriteMap::iterator SpriteSheet::find(const std::string& name)
{
	return std::find_if(m_sprites.begin(), m_sprites.end(),
		[&] (const std::pair<std::string, Sprite>& pair) {
			return pair.first == name;
		});
}



} // namespace gp
#endif
