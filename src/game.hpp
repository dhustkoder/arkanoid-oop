#ifndef ARKANOOP_GAME_HPP_
#define ARKANOOP_GAME_HPP_
#include "sprite_renderer.hpp"
#include "graphic_string.hpp"
#include "level.hpp"
#include "sprite.hpp"
#include "player.hpp"
#include "ball.hpp"
#include "bricks.hpp"

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

	void updateGameObjects(float frametime, float delta);
	void processCollisions();
	void renderGameObjects();

private:
	SpriteRenderer m_renderer;
	GraphicString m_infoStr;
	Level m_level;
	Sprite m_background;
	Player m_player;
	Ball m_ball;
	int m_points;
	bool m_presentingLevel;
};


} // namespace gp
#endif
