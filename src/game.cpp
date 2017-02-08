#include <iostream>
#include <tuple>
#include "game.hpp"


namespace gp {



Game::Game()
	: m_display("Arkanoid OOP", kWinWidth, kWinHeight),
	m_renderer(kWinWidth, kWinHeight),
	m_brickSprites("../data/sprites/pieces.png"),
	m_ballSprites("../data/sprites/pieces.png"),
	m_paddleSprites("../data/sprites/pieces.png"),
	m_backgroundImage("../data/sprites/bkg0.png"),
	m_background(m_backgroundImage),
	m_ball(m_ballSprites.getTexture()),
	m_player(m_paddleSprites.getTexture())
{
	m_display.setVsync(false);
	m_display.clear(0, 0, 0, 0);
	m_display.update();

	m_brickSprites.mapSprite("blue_brick", {8, 8}, {32, 16});
	m_brickSprites.mapSprite("blue_green_brick", {48, 8}, {32, 16});
	m_brickSprites.mapSprite("blue_red_brick", {84, 8}, {32, 16});
	m_brickSprites.mapSprite("blue_purple_brick", {120, 8}, {32, 16});
	m_brickSprites.mapSprite("blue_yellow_brick", {156, 8}, {32, 16});
	m_brickSprites.mapSprite("blue_black_brick", {192, 8}, {32, 16});
	m_brickSprites.mapSprite("blue_darkyellow_brick", {228, 8}, {32, 16});
	m_brickSprites.mapSprite("yellow_purple_brick", {264, 8}, {32, 16});
	m_brickSprites.mapSprite("green_brick", {8, 28}, {32, 16});
	m_brickSprites.mapSprite("green_red_brick", {48, 28}, {32, 16});
	m_brickSprites.mapSprite("green_purple_brick", {84, 28}, {32, 16});
	m_brickSprites.mapSprite("green_yellow_brick", {120, 28}, {32, 16});
	m_brickSprites.mapSprite("green_dark_brick", {156, 28}, {32, 16});
	m_brickSprites.mapSprite("green_darkyellow_brick", {192, 28}, {32, 16});
	m_brickSprites.mapSprite("dark_darkyellow_brick", {228, 28}, {32, 16});
	m_brickSprites.mapSprite("dark_purple_brick", {264, 28}, {32, 16});

	m_ballSprites.mapSprite("blue_ball", {48, 136}, {8, 8});
	m_paddleSprites.mapSprite("blue_paddle", {48, 72}, {64, 16});


	resetGame();
}


Game::~Game()
{

}


void Game::resetGame()
{
	resetPlayer();
	resetBall();
	resetBricks();
	resetBackground();
}


void Game::resetBricks()
{
	const Vec2f sprite_size {32, 16};
	Vec2f origin { (sprite_size.x + 8) / 2.0f, (sprite_size.y + 8) / 2.0f };

	const int lines = 10;
	const int brick_count = lines * (kWinWidth / static_cast<int>(sprite_size.x + 8));

	m_bricks.reserve(brick_count);

	for (int i = 0; i < brick_count; ++i) {
		m_bricks.emplace_back(m_brickSprites.getSprite(i % m_brickSprites.getSize()));
		m_bricks.back().setOrigin(origin);
		m_bricks.back().setSize(sprite_size);

		origin.x += sprite_size.x + 8;
		if (origin.x > (kWinWidth - ((sprite_size.x + 8) / 2.0f))) {
			origin.x = (sprite_size.x + 8) / 2.0f;
			origin.y += sprite_size.y + 8;
		}
	}
}


void Game::resetPlayer()
{
	const Vec2f default_player_size {64, 16};
	const Vec2f default_player_origin { kWinWidth / 2, kWinHeight - (default_player_size.y / 2.0f)};
	const float default_velocity = 265.0f;

	m_player = m_paddleSprites.getSprite("blue_paddle");
	m_player.setSize(default_player_size);
	m_player.setOrigin(default_player_origin);
	m_player.setVelocity(default_velocity);
}


void Game::resetBall()
{
	const Vec2f default_origin { kWinWidth / 2, kWinHeight / 2};
	const Vec2f default_velocity = { 200, 200 };
	const float default_radius = 8.0f;

	m_ball = m_ballSprites.getSprite("blue_ball");
	m_ball.setOrigin(default_origin);
	m_ball.setRadius(default_radius);
	m_ball.setVelocity(default_velocity);
}


void Game::resetBackground()
{
	const Texture& texture = m_background.getTexture();
	m_background.setOrigin({kWinWidth / 2, kWinHeight / 2});
	m_background.setSize({kWinWidth, kWinHeight});
	m_background.setUVPos({0, 0});
	m_background.setUVSize({texture.getWidth(), texture.getHeight()});
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
	m_player.update(delta, kWinWidth);
	m_ball.update(delta, kWinWidth, kWinHeight);
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
	if (m_bricks.back().getBottom() < m_ball.getTop())
		return;

	for (auto itr = m_bricks.begin(); itr != m_bricks.end(); ++itr) {
		if (m_ball.isIntersecting(*itr))
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

		m_bricks.erase(itr);
		break;
	}
}


inline void Game::renderGameObjects()
{
	m_renderer.begin();
	
	m_renderer.submit(m_background);
	m_renderer.submit(m_ball);

	for (const auto& brick : m_bricks) {
		m_renderer.submit(brick);
	}

	m_renderer.submit(m_player);

	m_renderer.end();
	m_renderer.flush();
}


} // namespace gp
