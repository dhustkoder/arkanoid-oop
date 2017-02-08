#ifndef ARKANOID_OOP_SPRITE_SHEET_HPP_
#define ARKANOID_OOP_SPRITE_SHEET_HPP_
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

#include "math_types.hpp"
#include "texture.hpp"
#include "sprite.hpp"


namespace gp {


class SpriteSheet {
	using SpriteMap = std::vector<std::pair<std::string, Sprite>>;
public:
	SpriteSheet(const std::string& texture_file_path)
		: m_texture(texture_file_path)
	{

	}

	~SpriteSheet()
	{

	}

	void mapSprite(std::string name, const Vec2f& uv_pos, const Vec2f& uv_size)
	{
		const auto itr = find(name);
		if (itr == m_sprites.end())
			m_sprites.emplace_back(std::move(name), Sprite(m_texture, {0, 0}, {0, 0}, uv_pos, uv_size));
		else
			itr->second = Sprite(m_texture, {0, 0}, {0, 0}, uv_pos, uv_size);
	}

	Sprite getSprite(const std::string& name) const
	{		
		const auto itr = find(name);
		if (itr == m_sprites.end())
			throw Exception("request for unmapped sprite: " + name);

		return Sprite(itr->second);
	}

	Sprite getSprite(const int index) const
	{
		return m_sprites.at(index).second;
	}

	const Texture& getTexture() const
	{
		return m_texture;
	}

	int getSize()
	{
		return static_cast<int>(m_sprites.size());
	}

private:

	SpriteMap::iterator find(const std::string& name)
	{
		return std::find_if(m_sprites.begin(), m_sprites.end(),
			[&] (const std::pair<std::string, Sprite>& pair) {
				return pair.first == name;
			});
	}

	SpriteMap::const_iterator find(const std::string& name) const
	{
		return std::find_if(m_sprites.cbegin(), m_sprites.cend(),
			[&] (const std::pair<std::string, Sprite>& pair) {
				return pair.first == name;
			});
	}


	Texture m_texture;
	SpriteMap m_sprites;
};




} // namespace gp
#endif
