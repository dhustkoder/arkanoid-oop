#ifndef ARKANOID_OOP_GAME_HPP_
#define ARKANOID_OOP_GAME_HPP_
#include <vector>
#include "display.hpp"
#include "sprite_renderer.hpp"
#include "ball.hpp"
#include "player.hpp"
#include "brick.hpp"

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
	void updateGameObjects(float delta);
	void checkCollisions();
	void renderGameObjects();

	void resetBricks();
	void resetPlayer();
	void resetBall();



private:
	Display m_display;
	SpriteRenderer m_renderer;
	Texture m_spritesheet;
	Ball m_ball;
	Player m_player;
	std::vector<Brick> m_bricks;
};


} // namespace gp
#endif
