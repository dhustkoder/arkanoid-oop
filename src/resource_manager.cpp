#include "resource_manager.hpp"

namespace gp {

ResourceManager::TextureMap ResourceManager::s_textureMap;
ResourceManager::SpriteSheetMap ResourceManager::s_spriteSheetMap;


void ResourceManager::initialize()
{
	loadTextures();
	loadSpriteSheets();
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

	SpriteSheet balls(getTexture("pieces"));
	balls.mapSprite("blue", {48, 136}, {8, 8});
	balls.mapSprite("green", {57, 136}, {8, 8});
	balls.mapSprite("red", {66, 136}, {8, 8});
	balls.mapSprite("purple", {75, 136}, {8, 8});
	balls.mapSprite("yellow", {84, 136}, {8, 8});
	balls.mapSprite("black", {93, 136}, {8, 8});
	balls.mapSprite("dark_yellow", {102, 136}, {8, 8});

	SpriteSheet paddles(getTexture("pieces"));
	paddles.mapSprite("blue", {48, 72}, {64, 16});


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

	s_spriteSheetMap.emplace_back(std::make_pair(std::string("fontset"), std::move(fontset)));
	s_spriteSheetMap.emplace_back(std::make_pair(std::string("balls"), std::move(balls)));
	s_spriteSheetMap.emplace_back(std::make_pair(std::string("paddles"), std::move(paddles)));
	s_spriteSheetMap.emplace_back(std::make_pair(std::string("bricks"), std::move(bricks)));
}


} // namespace gp

