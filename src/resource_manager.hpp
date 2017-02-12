#ifndef ARKANOOP_RESOURCE_MANAGER_HPP_
#define ARKANOOP_RESOURCE_MANAGER_HPP_
#include <cctype>
#include <vector>
#include <string>
#include <algorithm>

#include "exception.hpp"
#include "texture.hpp"
#include "sprite_sheet.hpp"


namespace gp {



class ResourceManager {
	using TextureMap = std::vector<std::pair<std::string, Texture>>;
	using SpriteSheetMap = std::vector<std::pair<std::string, SpriteSheet>>;

public:
	static void initialize();
	static void terminate();
	static const Texture& getTexture(std::string name);
	static const SpriteSheet& getSpriteSheet(std::string name);



private:
	static TextureMap::iterator findTexture(const std::string& name);
	static SpriteSheetMap::iterator findSpriteSheet(const std::string& name);
	static void loadTextures();
	static void loadSpriteSheets();


private:
	static TextureMap s_textureMap;
	static SpriteSheetMap s_spriteSheetMap;
};



inline const Texture& ResourceManager::getTexture(std::string name)
{
	const auto itr = findTexture(name);
	if (itr == s_textureMap.end())
	       throw Exception("Couldn't find texture with name \'" + name + "\'");

	return itr->second;
}


inline const SpriteSheet& ResourceManager::getSpriteSheet(std::string name)
{
	const auto itr = findSpriteSheet(name);
	if (itr == s_spriteSheetMap.end())
	       throw Exception("Couldn't find sprite sheet with name \'" + name + "\'");

	return itr->second;
}


inline ResourceManager::TextureMap::iterator ResourceManager::findTexture(const std::string& name)
{
	const auto itr = std::find_if(s_textureMap.begin(), s_textureMap.end(),
	                           [name] (const TextureMap::value_type& pair) {
				   	return pair.first == name; 
				   });
	return itr;
}


inline ResourceManager::SpriteSheetMap::iterator ResourceManager::findSpriteSheet(const std::string& name)
{
	const auto itr = std::find_if(s_spriteSheetMap.begin(), s_spriteSheetMap.end(),
	                           [name] (const SpriteSheetMap::value_type& pair) {
				   	return pair.first == name; 
				   });
	return itr;
}


} // namespace gp
#endif

