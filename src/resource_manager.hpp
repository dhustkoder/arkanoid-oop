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
	template<class T>
	static typename T::iterator findResource(const std::string& name, T* map);

	static void loadTextures();
	static void loadSpriteSheets();
	static void loadLevels();

private:
	static TextureMap s_textureMap;
	static SpriteSheetMap s_spriteSheetMap;
	static LevelMap s_levelMap;
};


template<class T>
typename T::iterator ResourceManager::findResource(const std::string& name, T* const map)
{
	const auto itr = std::find_if(map->begin(), map->end(),
				[&name] (const typename T::value_type& elem) {
					return elem.first == name;
				});
	return itr;
}


template<>
inline ResourceManager::LevelMap::iterator ResourceManager::findResource(const std::string& name, LevelMap* const map)
{
	const auto itr = std::find_if(map->begin(), map->end(),
				[&name] (const typename LevelMap::value_type& elem) {
					return elem.getName() == name;
				});
	return itr;
}


inline const Texture& ResourceManager::getTexture(std::string name)
{
	const auto itr = findResource(name, &s_textureMap);
	if (itr == s_textureMap.end())
	       throw Exception("Couldn't find texture with name \'" + name + "\'");

	return itr->second;
}


inline const SpriteSheet& ResourceManager::getSpriteSheet(std::string name)
{
	const auto itr = findResource(name, &s_spriteSheetMap);
	if (itr == s_spriteSheetMap.end())
	       throw Exception("Couldn't find sprite sheet with name \'" + name + "\'");

	return itr->second;
}


inline const Level& ResourceManager::getLevel(std::string name)
{
	const auto itr = findResource(name, &s_levelMap);
	if (itr == s_levelMap.end())
	       throw Exception("Couldn't find Level with name \'" + name + "\'");

	return *itr;
}


inline const Level& ResourceManager::getLevel(int index)
{
	return s_levelMap.at(index);
}





} // namespace gp
#endif

