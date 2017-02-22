#include <iostream>

#include "game.hpp"
#include "display.hpp"
#include "resource_manager.hpp"

namespace gp {


Game::Game() :
	m_infoStr("", {0, Display::getViewSize().y - 50}, 2, 2),
	m_background(ResourceManager::getTexture("bkg0"))
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
	m_points = 0;
	m_levelIndex = 0;
	setLevel(m_levelIndex++);
}


void Game::setBackground(const int index)
{
	const Texture& texture = ResourceManager::getTexture("bkg" + std::to_string(index));
	m_background = Sprite(texture, Display::getViewSize() / 2.0f, Display::getViewSize(),
	                      {0, 0}, texture.getSize());

}


void Game::setLevel(const int index)
{
	m_levelName = ResourceManager::getLevel(index).getName();
	m_bricks = ResourceManager::getLevel(index).getBricks();

	m_player.reset(0);
	m_ball.reset(0);
	m_ball.stuckIntoPlayer(m_player);

	setBackground(index);
	m_presentingLevel = true;
	m_levelPresentationStartTime = glfwGetTime();
}


void Game::run()
{
	double lasttime = 0;
	double lastsecond = 0;
	int fps = 0;

	while (!Display::shouldClose()) {
		m_time = glfwGetTime();
		m_delta = static_cast<float>(m_time - lasttime);
		lasttime = m_time;

		Display::clear(0.25f, 0.25f, 0.65f, 1.0f);
		
		updateGameObjects();
		renderGameObjects();

		Display::update();

		++fps;
		if ((m_time - lastsecond) >= 1.0f) {
			m_infoStr.setString("BRICKS DESTROYED:" + std::to_string(m_points) +
			                    "\nFPS:" + std::to_string(fps));
			fps = 0;
			lastsecond = m_time;
		}

	}
}


inline void Game::updateGameObjects()
{
	if (m_presentingLevel) {

		if ((m_time - m_levelPresentationStartTime) < 5.0f) {

			const Vec4f color {
				1,
				1,
				1,
				1 * sinf(m_time - m_levelPresentationStartTime)
			};

			m_levelName.setColor(color);

		} else {
			m_presentingLevel = false;
		}

	} else {

		m_player.update(m_delta);
		m_ball.update(m_delta);

		if (!m_ball.isStuckIntoPlayer())
			processCollisions();

		if (m_bricks.getBricks().size() == 0)
			setLevel(m_levelIndex++);
	}
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
	m_renderer.submit(m_infoStr);

	if (m_presentingLevel)
		m_renderer.submit(m_levelName);

	m_renderer.end();
	m_renderer.flush();
}


} // namespace gp

