#include <iostream>
#include <tuple>
#include "game.hpp"


namespace gp {


Game::Game() :
	m_display("Arkanoid OOP", kWinWidth, kWinHeight),
	m_renderer(kWinWidth, kWinHeight),

	m_backgroundTextures{Texture("../data/sprites/bkg0.png"),
	                     Texture("../data/sprites/bkg1.png"),
	                     Texture("../data/sprites/bkg2.png"),
	                     Texture("../data/sprites/bkg3.png")},

	m_piecesTexture("../data/sprites/pieces.png"),

	m_background(m_backgroundTextures[0]),
	m_player(m_piecesTexture, kWinWidth, kWinHeight),
	m_ball(m_piecesTexture, kWinWidth, kWinHeight),
	m_bricks(m_piecesTexture, kWinWidth, kWinHeight)

{
	m_display.setVsync(false);
	m_display.clear(0, 0, 0, 0);
	m_display.update();


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
	m_renderer.submit(m_ball);

	for (const auto& brick : m_bricks.getBricks())
		m_renderer.submit(brick);

	m_renderer.submit(m_player);

	m_renderer.end();
	m_renderer.flush();
}


} // namespace gp
