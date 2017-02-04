#include <iostream>
#include <tuple>
#include "game.hpp"


namespace gp {



Game::Game()
	: m_display("Arkanoid OOP", 800, 600),
	m_renderer(Shader("../shaders/simple_tex.vs", "../shaders/simple_tex.fs")),
	m_spritesheet("../spritesheet.png"),
	m_ball(m_spritesheet),
	m_player(m_spritesheet)
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
	const Vec2f uv_size { 64, 32 };

	const Vec2f uv_positions[8] {
		{ 0, 0 },
		{ 72, 0},
		{144, 0},
		{216, 0},
		{ 0, 40},
		{72, 40},
		{144, 40},
		{216, 40}
	};

	const Vec2f sprite_size = uv_size / 2.0f;
	Vec2f origin = { (sprite_size.x * 2) + 8, sprite_size.y + 8 };

	for (int i = 0; i < 60; ++i) {
		m_bricks.emplace_back(Sprite(m_spritesheet, origin, sprite_size, uv_positions[i % 8], uv_size));
		origin.x += (sprite_size.x * 2) + 8;
		if (origin.x >= (800 - 8 - (sprite_size.x * 2))) {
			origin.x = (sprite_size.x * 2) + 8;
			origin.y += (sprite_size.y * 2) + 8;
		}
	}
}


void Game::resetPlayer()
{
	const Vec2f default_uv_pos { 184, 111 };
	const Vec2f default_uv_size { 96, 25 };
	const Vec2f default_player_size = (default_uv_size / 2.0f);
	const Vec2f default_player_origin { 800 / 2, 600 - default_player_size.y};
	const float default_velocity = 150.0f;

	m_player.setUVPos(default_uv_pos);
	m_player.setUVSize(default_uv_size);
	m_player.setSize(default_player_size);
	m_player.setOrigin(default_player_origin);
	m_player.setVelocity(default_velocity);
}


void Game::resetBall()
{
	const Vec2f default_uv_pos { 0, 80 };
	const Vec2f default_uv_size { 24, 24 };
	const Vec2f default_origin { 800 / 2, 600 / 2};
	const Vec2f default_velocity = { 150, 150 };
	const float default_radius = default_uv_size.x / 2.0f;

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
		m_display.clear(0.2f, 0.2f, 0.9f, 1.0f);

		frametime = glfwGetTime();
		delta = static_cast<float>(frametime - lastframetime);
		lastframetime = frametime;

		updateGameObjects(delta);
		checkCollisions();
		renderGameObjects();

		m_display.update();


		// fps count
		++fps;
		if ((frametime - lastsecond) >= 1.0f) {
			std::cout << "FPS: " << fps << '\n';
			std::cout << "BALL ORIGIN: " << m_ball.getOrigin() << '\n';
			std::cout << "PLAYER ORIGIN: " << m_player.getOrigin() << '\n';
			std::cout << "BALL RADIUS: " << m_ball.getRadius() << '\n';
			std::cout << "PLAYER SIZE: " << m_player.getSize() << '\n';
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


void Game::updateGameObjects(const float delta)
{
	m_player.update(delta);
	m_ball.update(delta);
}


inline void Game::checkCollisions()
{
	if (m_ball.intersects(m_player)) {
		m_ball.setVelocity({m_ball.getVelocity().x, -std::abs(m_ball.getVelocity().y)});
	}

	for (auto itr = m_bricks.begin(); itr != m_bricks.end(); ++itr) {
		if (m_ball.intersects(*itr)) {

			const auto& ball_origin = m_ball.getOrigin();
			const auto& brick_origin = itr->getOrigin();

			const Vec2f diff = ball_origin - brick_origin;
			
			m_ball.setVelocity({diff.x <= 0.0f ? -std::abs(m_ball.getVelocity().x) :
			                    std::abs(m_ball.getVelocity().x),
					    diff.y <= 0.0f ? -std::abs(m_ball.getVelocity().y) :
					    std::abs(m_ball.getVelocity().y)});

			m_bricks.erase(itr);
			break;
		}
	}

}


inline void Game::renderGameObjects()
{
	m_renderer.begin();
	
	m_renderer.submit(m_ball);

	for (const auto& brick : m_bricks)
		m_renderer.submit(brick);

	m_renderer.submit(m_player);
	
	m_renderer.end();

	m_renderer.flush();
}


} // namespace gp
