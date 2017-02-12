#include <iostream>
#include <tuple>
#include "resource_manager.hpp"
#include "graphic_string.hpp"
#include "game.hpp"

namespace gp {


Game::Game() :
	m_display("Arkanoid OOP", kWinWidth, kWinHeight),
	m_renderer(kWinWidth, kWinHeight),
	m_piecesTexture("../data/sprites/pieces.png"),
	m_letters(m_piecesTexture),
	m_background(m_backgroundTextures[0]),
	m_player(m_piecesTexture, kWinWidth, kWinHeight),
	m_ball(m_piecesTexture, kWinWidth, kWinHeight),
	m_bricks(m_piecesTexture, kWinWidth, kWinHeight)

{
	m_display.setVsync(false);
	m_display.clear(0, 0, 0, 0);
	m_display.update();

	ResourceManager::loadTexture("bkg0", "../data/sprites/bkg0.png");
	ResourceManager::loadTexture("bkg1", "../data/sprites/bkg1.png");
	ResourceManager::loadTexture("bkg2", "../data/sprites/bkg2.png");
	ResourceManager::loadTexture("bkg3", "../data/sprites/bkg3.png");

	m_letters.mapSprite("A", {304, 8}, {5, 8}); 
	m_letters.mapSprite("B", {310, 8}, {5, 8});
	m_letters.mapSprite("C", {316, 8}, {5, 8});
	m_letters.mapSprite("D", {322, 8}, {5, 8});
	m_letters.mapSprite("E", {328, 8}, {5, 8});
	m_letters.mapSprite("F", {334, 8}, {5, 8});
	m_letters.mapSprite("G", {340, 8}, {5, 8});
	m_letters.mapSprite("H", {304,17}, {5, 8});
	m_letters.mapSprite("I", {310,17}, {5, 8});
	m_letters.mapSprite("J", {316,17}, {5, 8});
	m_letters.mapSprite("K", {322,17}, {5, 8});
	m_letters.mapSprite("L", {328,17}, {5, 8});
	m_letters.mapSprite("M", {334,17}, {5, 8});
	m_letters.mapSprite("N", {340,17}, {5, 8});
	m_letters.mapSprite("O", {304,26}, {5, 8});
	m_letters.mapSprite("P", {310,26}, {5, 8});
	m_letters.mapSprite("Q", {316,26}, {5, 8});
	m_letters.mapSprite("R", {322,26}, {5, 8});
	m_letters.mapSprite("S", {328,26}, {5, 8});
	m_letters.mapSprite("T", {334,26}, {5, 8});
	m_letters.mapSprite("U", {340,26}, {5, 8});
	m_letters.mapSprite("V", {304,35}, {5, 8});
	m_letters.mapSprite("W", {310,35}, {5, 8});
	m_letters.mapSprite("X", {316,35}, {5, 8});
	m_letters.mapSprite("Y", {322,35}, {5, 8});
	m_letters.mapSprite("Z", {328,35}, {5, 8});
	m_letters.mapSprite("!", {329,57}, {2, 8});

	resetGame();
}


Game::~Game()
{

}


void Game::resetGame()
{
	m_player.reset(0);
	m_ball.reset(0);
	m_bricks.reset(10);
	resetBackground(0);
}


void Game::resetBackground(const int index)
{
	const Texture& texture = m_backgroundTextures[index];
	m_background = Sprite(texture, {kWinWidth / 2.0f, kWinHeight / 2.0f},
	                      {kWinWidth, kWinHeight}, {0, 0}, texture.getSize());
}


void Game::run()
{
	double frametime = 0;
	double lastframetime = 0;
	double lastsecond = 0;
	float delta;
	int fps = 0;

	while (!m_display.shouldClose()) {
		frametime = glfwGetTime();
		delta = static_cast<float>(frametime - lastframetime);
		lastframetime = frametime;

		m_display.clear(0.25f, 0.25f, 0.65f, 1.0f);

		updateGameObjects(delta);
		renderGameObjects();

		m_display.update();


		++fps;
		if ((frametime - lastsecond) >= 1.0f) {
			std::cout << "FPS: " << fps << '\n';
			fps = 0;
			lastsecond = frametime;
		}
	}
}


inline void Game::updateGameObjects(const float delta)
{
	m_player.update(delta);
	m_ball.update(delta);
	m_bricks.update(delta);
	processCollisions();
}


inline void Game::processCollisions()
{
	if (m_ball.isIntersecting(m_player)) {

		const GLfloat y_vel = -std::abs(m_ball.getVelocity().y);
		GLfloat x_vel;

		// check if collided against the paddle edges
		if (m_ball.getOrigin().x < (m_player.getLeft() + 16))
			x_vel = -std::abs(m_ball.getVelocity().x);
		else if (m_ball.getOrigin().x > (m_player.getRight() - 16))
			x_vel = std::abs(m_ball.getVelocity().x);
		else
			x_vel = m_ball.getVelocity().x;

		m_ball.setVelocity({x_vel, y_vel});

		return;
	}

	// skip tests if ball is not as high as the lowest brick
	if (m_bricks.getBricks().back().getBottom() < m_ball.getTop())
		return;

	for (auto itr = m_bricks.getBricks().begin(); itr != m_bricks.getBricks().end(); ++itr) {
		if (!m_ball.isIntersecting(*itr))
			continue;

		if (m_ball.getOrigin().x >= itr->getLeft() &&
		    m_ball.getOrigin().x <= itr->getRight()) {

			const GLfloat abs_y_vel = std::abs(m_ball.getVelocity().y);
			GLfloat new_y_vel;

			if (m_ball.getOrigin().y < itr->getOrigin().y)
				new_y_vel = -abs_y_vel;
			else
				new_y_vel = abs_y_vel;

			m_ball.setVelocity({m_ball.getVelocity().x, new_y_vel});

		} else {
			
			const GLfloat abs_x_vel = std::abs(m_ball.getVelocity().x);
			GLfloat new_x_vel;

			if (m_ball.getOrigin().x < itr->getOrigin().x)
				new_x_vel = -abs_x_vel;
			else
				new_x_vel = abs_x_vel;
			
			m_ball.setVelocity({new_x_vel, m_ball.getVelocity().y});
		}

		m_bricks.getBricks().erase(itr);
		break;
	}
}


inline void Game::renderGameObjects()
{
	m_renderer.begin();
	
	m_renderer.submit(m_background);
	m_renderer.submit(m_bricks.getBricks());
	m_renderer.submit(m_ball);
	m_renderer.submit(m_player);

	static const GraphicString newgame("new game", {400, 300}, m_letters, 2.0f, 2.0f, {1, 0, 0, 1});
	static const GraphicString loadgame("load game", {400, 320}, m_letters, 2.0f, 2.0f, {1, 0, 0, 1});
	m_renderer.submit(newgame.getSprites());
	m_renderer.submit(loadgame.getSprites());


	m_renderer.end();
	m_renderer.flush();
}


} // namespace gp
