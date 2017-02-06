#include <iostream>
#include <tuple>
#include "game.hpp"


namespace gp {



Game::Game()
	: m_display("Arkanoid OOP", kWinWidth, kWinHeight),
	m_renderer(kWinWidth, kWinHeight),
	m_pieces("../data/sprites/pieces.png"),
	m_bkgImage("../data/sprites/bkg0.png"),
	m_background(m_bkgImage, {kWinWidth / 2, kWinHeight / 2}, {1600, 1200}, {0, 0}, {1600, 1200}),
	m_ball(Sprite(m_pieces)),
	m_player(Sprite(m_pieces))
{
	m_display.setVsync(false);
	m_display.clear(0, 0, 0, 0);
	m_display.update();
	resetGame();
}


Game::~Game()
{

}


void Game::resetBricks()
{
	m_destroyedBricks = 0;

	const Vec2f uv_size { 32, 16 };
	const Vec2f uv_positions[8] {
		{ 8,    8 }, { 48,   8 }, { 84,  8 }, { 120,  8 },
		{ 8,   28 }, { 48,  28 }, { 84, 28 }, { 120, 28 }
	};

	const Vec2f sprite_size = uv_size;
	Vec2f origin = { (sprite_size.x / 2) + 8, (sprite_size.y / 2) + 8};

	const int lines = 10;
	const int brick_count = lines * (kWinWidth / (sprite_size.x + 8));

	m_bricks.reserve(brick_count);

	for (int i = 0; i < brick_count; ++i) {
		m_bricks.emplace_back(Sprite(m_pieces, origin, sprite_size, uv_positions[i % 8], uv_size));
		origin.x += sprite_size.x + 8;
		if (origin.x >= (kWinWidth - (sprite_size.x + 8))) {
			origin.x = (sprite_size.x/2) + 8;
			origin.y += sprite_size.y + 8;
		}
	}
}


void Game::resetPlayer()
{
	const Vec2f default_uv_pos { 8, 151 };
	const Vec2f default_uv_size { 64, 20 };
	const Vec2f default_player_size = default_uv_size;
	const Vec2f default_player_origin { kWinWidth / 2, kWinHeight - (default_player_size.y / 2.0f)};
	const float default_velocity = 265.0f;

	m_player.setUVPos(default_uv_pos);
	m_player.setUVSize(default_uv_size);
	m_player.setSize(default_player_size);
	m_player.setOrigin(default_player_origin);
	m_player.setVelocity(default_velocity);
}


void Game::resetBall()
{
	const Vec2f default_uv_pos { 48, 136 };
	const Vec2f default_uv_size { 8, 8 };
	const Vec2f default_origin { kWinWidth / 2, kWinHeight / 2};
	const Vec2f default_velocity = { 200, 200 };
	const float default_radius = (default_uv_size.x + default_uv_size.y) / 2.0f;

	m_ball.setUVPos(default_uv_pos);
	m_ball.setUVSize(default_uv_size);
	m_ball.setOrigin(default_origin);
	m_ball.setRadius(default_radius);
	m_ball.setVelocity(default_velocity);
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


void Game::resetGame()
{
	resetPlayer();
	resetBall();
	resetBricks();
}


inline void Game::updateGameObjects(const float delta)
{
	m_player.update(delta, kWinWidth);
	m_ball.update(delta, kWinWidth, kWinHeight);
	processCollisions();

	if (m_destroyedBricks > 15) {
		const auto is_destroyed = [](const Brick& brick) {
			return brick.isDestroyed();
		};

		const auto begin = m_bricks.begin();
		const auto end = m_bricks.end();

		m_bricks.erase(std::remove_if(begin, end, is_destroyed), end);
		m_destroyedBricks = 0;
	}
}


inline void Game::processCollisions()
{
	if (m_ball.isIntersecting(m_player)) {

		const GLfloat y_vel = -std::abs(m_ball.getVelocity().y);
		GLfloat x_vel;

		// check if collided against the paddle edges
		if (m_ball.getOrigin().x < (m_player.getLeft() + 24))
			x_vel = -std::abs(m_ball.getVelocity().x);
		else if (m_ball.getOrigin().x > (m_player.getRight() - 24))
			x_vel = std::abs(m_ball.getVelocity().x);
		else
			x_vel = m_ball.getVelocity().x;

		m_ball.setVelocity({x_vel, y_vel});

		return;
	}

	// skip tests if ball is not as high as the lowest brick
	if (m_bricks.back().getBottom() < m_ball.getTop())
		return;

	for (auto itr = m_bricks.end() - 1; itr != m_bricks.begin() - 1; --itr) {
		if (itr->isDestroyed() || !m_ball.isIntersecting(*itr))
			continue;

		if (m_ball.getOrigin().x >= itr->getLeft() && m_ball.getOrigin().x <= itr->getRight()) {

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

		itr->destroy();
		++m_destroyedBricks;
		break;
	}
}


inline void Game::renderGameObjects()
{
	m_renderer.begin();
	
	m_renderer.submit(m_background);
	m_renderer.submit(m_ball);

	for (const auto& brick : m_bricks) {
		if (!brick.isDestroyed())
			m_renderer.submit(brick);
	}

	m_renderer.submit(m_player);

	m_renderer.end();
	m_renderer.flush();
}


} // namespace gp
