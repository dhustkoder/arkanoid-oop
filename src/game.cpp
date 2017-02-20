#include <iostream>

#include "game.hpp"
#include "display.hpp"
#include "resource_manager.hpp"

namespace gp {


Game::Game() :
	m_infoStr("", {0, Display::getViewSize().y - 50}, 2, 2),
	m_background(ResourceManager::getTexture("bkg0")),
	m_points(0)
{
	Display::setVsync(false);
	Display::clear(0, 0, 0, 0);
	Display::update();
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
	const Texture& texture = ResourceManager::getTexture("bkg" + std::to_string(index));
	m_background = Sprite(texture, Display::getViewSize() / 2.0f, Display::getViewSize(),
	                      {0, 0}, texture.getSize());

}


void Game::run()
{
	double frametime = 0;
	double lastframetime = 0;
	double lastsecond = 0;
	float delta;
	int fps = 0;

	while (!Display::shouldClose()) {
		frametime = glfwGetTime();
		delta = static_cast<float>(frametime - lastframetime);
		lastframetime = frametime;

		Display::clear(0.25f, 0.25f, 0.65f, 1.0f);

		updateGameObjects(delta);
		renderGameObjects();

		Display::update();		

		++fps;
		if ((frametime - lastsecond) >= 1.0f) {
			m_infoStr.setString("BRICKS DESTROYED:" + std::to_string(m_points) +
			                    "\nFPS:" + std::to_string(fps));
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

		itr->hit();
		if (itr->isDestroyed()) {
			++m_points;
			const auto& oldstr = m_infoStr.getString();
			const auto fps_num_beg = oldstr.find("\n") + 5;
			const auto fps_num_end = oldstr.size() - fps_num_beg;

			m_infoStr.setString("BRICKS DESTROYED:" + std::to_string(m_points) +
			                    "\nFPS:" + oldstr.substr(fps_num_beg, fps_num_end));
			m_bricks.getBricks().erase(itr);
		}
		
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
	
	m_renderer.submit(m_infoStr.getSprites());

	m_renderer.end();
	m_renderer.flush();
}


} // namespace gp
