#ifndef ARKANOID_OOP_RESOURCE_MANAGER_HPP_
#define ARKANOID_OOP_RESOURCE_MANAGER_HPP_
#include <cctype>
#include <vector>
#include <string>
#include <algorithm>

#include "exception.hpp"
#include "texture.hpp"


namespace gp {



class ResourceManager {
	using TextureMap = std::vector<std::pair<std::string, Texture>>;
public:
	static void loadTexture(std::string name, std::string filepath);
	static const Texture& getTexture(std::string name);

private:
	static TextureMap::iterator find(const std::string& name);
	static TextureMap s_textures;
};


inline void ResourceManager::loadTexture(std::string name, std::string filepath)
{
	for (auto& c : name)
		c = std::toupper(c);

	const auto itr = find(name);
	if (itr == s_textures.end())
		s_textures.emplace_back(std::make_pair(std::move(name), Texture(std::move(filepath))));
	else
		itr->second = Texture(std::move(filepath));
}


inline const Texture& ResourceManager::getTexture(std::string name)
{
	const auto itr = find(name);
	if (itr == s_textures.end())
	       throw Exception("Couldn't find texture with name \'" + name + "\'");

	return itr->second;
}


inline ResourceManager::TextureMap::iterator ResourceManager::find(const std::string& name)
{
	const auto itr = std::find_if(s_textures.begin(), s_textures.end(),
	                           [name] (const TextureMap::value_type& pair) {
				   	return pair.first == name; 
				   });
	return itr;
}


}
#endif

