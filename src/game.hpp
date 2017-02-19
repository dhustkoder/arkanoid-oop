#ifndef ARKANOOP_GAME_HPP_
#define ARKANOOP_GAME_HPP_
#include <vector>
#include "display.hpp"
#include "sprite_sheet.hpp"
#include "sprite_renderer.hpp"
#include "ball.hpp"
#include "player.hpp"
#include "bricks.hpp"
#include "graphic_string.hpp"


namespace gp {


class Game {
public:
	Game(Game&) = delete;
	Game& operator=(Game&) = delete;

	Game();
	~Game();

	void run();

private:
	void resetGame();
	void resetBackground(int index);

	void updateGameObjects(float delta);
	void processCollisions();
	void renderGameObjects();

private:
	SpriteRenderer m_renderer;
	GraphicString m_infoStr;
	Sprite m_background;
	Player m_player;
	Ball m_ball;
	Bricks m_bricks;
	int m_points;
};


} // namespace gp
#endif
