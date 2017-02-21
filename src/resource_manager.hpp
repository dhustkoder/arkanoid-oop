#ifndef ARKANOOP_RESOURCE_MANAGER_HPP_
#define ARKANOOP_RESOURCE_MANAGER_HPP_
#include <cctype>
#include <vector>
#include <string>
#include <algorithm>

#include "exception.hpp"
#include "texture.hpp"
#include "sprite_sheet.hpp"
#include "level.hpp"


namespace gp {



class ResourceManager {
	using TextureMap = std::vector<std::pair<std::string, Texture>>;
	using SpriteSheetMap = std::vector<std::pair<std::string, SpriteSheet>>;
	using LevelMap = std::vector<Level>;
public:
	ResourceManager() = delete;

	static void initialize();
	static void terminate();
	static const Texture& getTexture(std::string name);
	static const SpriteSheet& getSpriteSheet(std::string name);
	static const Level& getLevel(std::string name);
	static const Level& getLevel(int index);

private:
	static TextureMap::iterator findTexture(const std::string& name);
	static SpriteSheetMap::iterator findSpriteSheet(const std::string& name);
	static LevelMap::iterator findLevel(const std::string& name);
	static void loadTextures();
	static void loadSpriteSheets();
	static void loadLevels();

private:
	static TextureMap s_textureMap;
	static SpriteSheetMap s_spriteSheetMap;
	static LevelMap s_levelMap;
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


inline const Level& ResourceManager::getLevel(std::string name)
{
	const auto itr = findLevel(name);
	if (itr == s_levelMap.end())
	       throw Exception("Couldn't find Level with name \'" + name + "\'");

	return *itr;
}


inline const Level& ResourceManager::getLevel(int index)
{
	return s_levelMap.at(index);
}


inline ResourceManager::TextureMap::iterator ResourceManager::findTexture(const std::string& name)
{
	const auto itr = std::find_if(s_textureMap.begin(), s_textureMap.end(),
	                           [&name] (const TextureMap::value_type& pair) {
				   	return pair.first == name; 
				   });
	return itr;
}


inline ResourceManager::SpriteSheetMap::iterator ResourceManager::findSpriteSheet(const std::string& name)
{
	const auto itr = std::find_if(s_spriteSheetMap.begin(), s_spriteSheetMap.end(),
	                           [&name] (const SpriteSheetMap::value_type& pair) {
				   	return pair.first == name; 
				   });
	return itr;
}


inline ResourceManager::LevelMap::iterator ResourceManager::findLevel(const std::string& name)
{
	const auto itr = std::find_if(s_levelMap.begin(), s_levelMap.end(),
	                           [&name] (const LevelMap::value_type& level){
				   	return level.getName() == name;
				   });
	return itr;
}


} // namespace gp
#endif

