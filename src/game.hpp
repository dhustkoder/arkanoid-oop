#ifndef ARKANOID_OOP_GAME_HPP_
#define ARKANOID_OOP_GAME_HPP_
#include <vector>
#include "display.hpp"
#include "sprite_sheet.hpp"
#include "sprite_renderer.hpp"
#include "ball.hpp"
#include "player.hpp"
#include "bricks.hpp"

namespace gp {


class Game {
	static constexpr const int kViewWidth = Display::kDefaultWidth;
	static constexpr const int kViewHeight = Display::kDefaultHeight;
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
	Sprite m_background;
	Player m_player;
	Ball m_ball;
	Bricks m_bricks;
};


} // namespace gp
#endif
