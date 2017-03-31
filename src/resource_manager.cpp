#include <iostream>
#include <fstream>
#include "resource_manager.hpp"

namespace gp {

ResourceManager::TextureMap ResourceManager::s_textureMap;
ResourceManager::SpriteSheetMap ResourceManager::s_spriteSheetMap;
ResourceManager::LevelMap ResourceManager::s_levelMap;

void ResourceManager::initialize()
{
	loadTextures();
	loadSpriteSheets();
	loadLevels();
}


void ResourceManager::terminate()
{
	s_textureMap.clear();
	s_spriteSheetMap.clear();
}


inline void ResourceManager::loadTextures()
{
	s_textureMap.clear();
	s_textureMap.reserve(10);

	s_textureMap.emplace_back(std::make_pair(std::string("bkg0"), Texture("../data/sprites/bkg0.png")));
	s_textureMap.emplace_back(std::make_pair(std::string("bkg1"), Texture("../data/sprites/bkg1.png")));
	s_textureMap.emplace_back(std::make_pair(std::string("bkg2"), Texture("../data/sprites/bkg2.png")));
	s_textureMap.emplace_back(std::make_pair(std::string("bkg3"), Texture("../data/sprites/bkg3.png")));
	s_textureMap.emplace_back(std::make_pair(std::string("pieces"), Texture("../data/sprites/pieces.png")));
	s_textureMap.emplace_back(std::make_pair(std::string("fontset"), Texture("../data/sprites/fontset.png")));
}


inline void ResourceManager::loadSpriteSheets()
{
	s_spriteSheetMap.clear();
	s_spriteSheetMap.reserve(10);

	SpriteSheet fontset(getTexture("fontset"));

	constexpr const char* const characteres[] {
		"!", "%", "\'", "(", ")", "*", "+", ",", "-", ".", "/",
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
		":", " ", "<", "=", ">", "?", "@",
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
		"K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
		"U", "V", "W", "X", "Y", "Z"
	};

	constexpr const int characteres_size = sizeof(characteres) / sizeof(characteres[0]);

	for (int i = 0; i < characteres_size; ++i)
		fontset.mapSprite(characteres[i], {i * 8, 0}, { 8, 8 });

	fontset.sort();

	SpriteSheet balls(getTexture("pieces"));
	balls.mapSprite("blue", {48, 136}, {8, 8});
	balls.mapSprite("green", {57, 136}, {8, 8});
	balls.mapSprite("red", {66, 136}, {8, 8});
	balls.mapSprite("purple", {75, 136}, {8, 8});
	balls.mapSprite("yellow", {84, 136}, {8, 8});
	balls.mapSprite("black", {93, 136}, {8, 8});
	balls.mapSprite("dark_yellow", {102, 136}, {8, 8});
	balls.sort();

	SpriteSheet paddles(getTexture("pieces"));
	paddles.mapSprite("blue", {48, 72}, {64, 16});
	paddles.sort();


	SpriteSheet bricks(getTexture("pieces"));
	bricks.mapSprite("blue_brick", {8, 8}, {32, 16});
	bricks.mapSprite("blue_green_brick", {48, 8}, {32, 16});
	bricks.mapSprite("blue_red_brick", {84, 8}, {32, 16});
	bricks.mapSprite("blue_purple_brick", {120, 8}, {32, 16});
	bricks.mapSprite("blue_yellow_brick", {156, 8}, {32, 16});
	bricks.mapSprite("blue_black_brick", {192, 8}, {32, 16});
	bricks.mapSprite("blue_darkyellow_brick", {228, 8}, {32, 16});
	bricks.mapSprite("yellow_purple_brick", {264, 8}, {32, 16});
	bricks.mapSprite("green_brick", {8, 28}, {32, 16});
	bricks.mapSprite("green_red_brick", {48, 28}, {32, 16});
	bricks.mapSprite("green_purple_brick", {84, 28}, {32, 16});
	bricks.mapSprite("green_yellow_brick", {120, 28}, {32, 16});
	bricks.mapSprite("green_dark_brick", {156, 28}, {32, 16});
	bricks.mapSprite("green_darkyellow_brick", {192, 28}, {32, 16});
	bricks.mapSprite("dark_darkyellow_brick", {228, 28}, {32, 16});
	bricks.mapSprite("dark_purple_brick", {264, 28}, {32, 16});
	bricks.sort();

	s_spriteSheetMap.emplace_back(std::make_pair(std::string("fontset"), std::move(fontset)));
	s_spriteSheetMap.emplace_back(std::make_pair(std::string("balls"), std::move(balls)));
	s_spriteSheetMap.emplace_back(std::make_pair(std::string("paddles"), std::move(paddles)));
	s_spriteSheetMap.emplace_back(std::make_pair(std::string("bricks"), std::move(bricks)));
}

void ResourceManager::loadLevels()
{
	const std::string file = [] {
		std::ifstream levels_file ("../data/levels/levels.dat", std::ios::ate);
		std::string str;

		const auto size = levels_file.tellg();

		if (size > 0)
			str.resize(static_cast<std::string::size_type>(size));
		else
			throw Exception("levels.dat: bad file");

		levels_file.seekg(levels_file.beg);

		std::copy(std::istreambuf_iterator<char>(levels_file),
		          std::istreambuf_iterator<char>(),
		          str.begin());

		return str;
	}();


	std::string name;
	std::string map;

	for (std::string::size_type i = 0; i < file.size(); ++i) {
		if (file[i] == '\"') {
			const auto level_name_beg = i + 1;
			
			for ( i = i + 1; i < file.size(); ++i) {
				if (file[i] == '\"')
					break;
			}

			if (i >= file.size())
				break;

			const auto level_name_end = i;
			name = file.substr(level_name_beg, level_name_end - level_name_beg);
			
			const auto level_bricks_beg = file.find_first_of("Bricks:", level_name_beg) + 7;
			const auto level_bricks_end = file.find_first_of('\n', level_bricks_beg);
			map = file.substr(level_bricks_beg, level_bricks_end - level_bricks_beg);

			std::cout << "NAME: " << name << '\n' << "MAP: " << map << '\n';
			s_levelMap.emplace_back(Level(name, map));
		}
	}
}

} // namespace gp

