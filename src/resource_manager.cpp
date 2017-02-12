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
}


inline void ResourceManager::loadSpriteSheets()
{
	s_spriteSheetMap.clear();
	s_spriteSheetMap.reserve(10);

	SpriteSheet alpha_numeric(getTexture("pieces"));
	alpha_numeric.mapSprite("A", {304, 8}, {5, 8}); 
	alpha_numeric.mapSprite("B", {310, 8}, {5, 8});
	alpha_numeric.mapSprite("C", {316, 8}, {5, 8});
	alpha_numeric.mapSprite("D", {322, 8}, {5, 8});
	alpha_numeric.mapSprite("E", {328, 8}, {5, 8});
	alpha_numeric.mapSprite("F", {334, 8}, {5, 8});
	alpha_numeric.mapSprite("G", {340, 8}, {5, 8});
	alpha_numeric.mapSprite("H", {304,17}, {5, 8});
	alpha_numeric.mapSprite("I", {310,17}, {2, 8});
	alpha_numeric.mapSprite("J", {316,17}, {5, 8});
	alpha_numeric.mapSprite("K", {322,17}, {5, 8});
	alpha_numeric.mapSprite("L", {328,17}, {5, 8});
	alpha_numeric.mapSprite("M", {334,17}, {5, 8});
	alpha_numeric.mapSprite("N", {340,17}, {5, 8});
	alpha_numeric.mapSprite("O", {304,26}, {5, 8});
	alpha_numeric.mapSprite("P", {310,26}, {5, 8});
	alpha_numeric.mapSprite("Q", {316,26}, {5, 8});
	alpha_numeric.mapSprite("R", {322,26}, {5, 8});
	alpha_numeric.mapSprite("S", {328,26}, {5, 8});
	alpha_numeric.mapSprite("T", {334,26}, {5, 8});
	alpha_numeric.mapSprite("U", {340,26}, {5, 8});
	alpha_numeric.mapSprite("V", {304,35}, {5, 8});
	alpha_numeric.mapSprite("W", {310,35}, {5, 8});
	alpha_numeric.mapSprite("X", {316,35}, {5, 8});
	alpha_numeric.mapSprite("Y", {322,35}, {5, 8});
	alpha_numeric.mapSprite("Z", {328,35}, {5, 8});
	alpha_numeric.mapSprite(" ", {334,35}, {5, 8});
	alpha_numeric.mapSprite("!", {329,57}, {2, 8});

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

	s_spriteSheetMap.emplace_back(std::make_pair(std::string("alpha_numeric"), std::move(alpha_numeric)));
	s_spriteSheetMap.emplace_back(std::make_pair(std::string("balls"), std::move(balls)));
	s_spriteSheetMap.emplace_back(std::make_pair(std::string("paddles"), std::move(paddles)));
	s_spriteSheetMap.emplace_back(std::make_pair(std::string("bricks"), std::move(bricks)));
}


} // namespace gp

