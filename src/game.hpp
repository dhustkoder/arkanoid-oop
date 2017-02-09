#ifndef ARKANOID_OOP_GAME_HPP_
#define ARKANOID_OOP_GAME_HPP_
#include <vector>
#include "display.hpp"
#include "sprite_sheet.hpp"
#include "sprite_renderer.hpp"
#include "ball.hpp"
#include "player.hpp"
#include "brick.hpp"

namespace gp {


class Game {
	static constexpr const int kWinWidth = 800;
	static constexpr const int kWinHeight = 600;
public:
	Game(Game&) = delete;
	Game& operator=(Game&) = delete;

	Game();
	~Game();

	void run();

private:
	void resetGame();
	void resetBricks();
	void resetPlayer();
	void resetBall();
	void resetBackground();

	void updateGameObjects(float delta);
	void processCollisions();
	void renderGameObjects();



private:
	Display m_display;
	SpriteRenderer m_renderer;
	SpriteSheet m_brickSprites;
	SpriteSheet m_ballSprites;
	SpriteSheet m_paddleSprites;
	
	Texture m_backgroundImage;
	Sprite m_background;
	Ball m_ball;
	Player m_player;
	std::vector<Sprite> m_bricks;
};


} // namespace gp
#endif
