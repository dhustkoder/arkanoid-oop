#include <ctime>
#include <iostream>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "exception.hpp"
#include "display.hpp"
#include "texture.hpp"
#include "keyboard.hpp"
#include "shader.hpp"
#include "sprite.hpp"
#include "sprite_renderer.hpp"



#define RUNNER

void game_main()
{
	using namespace gp;

	constexpr const int kWinWidth = 800;
	constexpr const int kWinHeight = 600;

	Display display("Hello GProj", kWinWidth, kWinHeight);
	display.setVsync(false);

#ifdef RUNNER

	constexpr int sprite_width = 180 / 4;
	constexpr int sprite_height = 180 / 4;


	Texture spritesheet("spritesheet.png");
	std::vector<Sprite> quads;
	quads.reserve(13);

	for (int i = 0; i < 13; ++i) {
		const int posx = sprite_width * (i % 4);
		const int posy = sprite_height * (i / 4);
		quads.emplace_back(Sprite(spritesheet, {400, 300}, {sprite_width * 4, sprite_height * 4}, {posx, posy}, {sprite_width, sprite_height}));
		quads.back().flipHorizontally();
		quads.back().flipVertically();
	}

#elif defined(VEGETA)

	Texture vegetasheet("vegeta.png");
	std::vector<Sprite> quads;
	quads.reserve(12);
	quads.emplace_back(Sprite(vegetasheet, {400, 300}, {53, 70}, {20, 551}, {53, 70}));
	quads.emplace_back(Sprite(vegetasheet, {400, 300}, {76, 94}, {93, 533}, {76, 94}));
//	quads.emplace_back(Sprite(vegetasheet, {400, 300}, {76, 94}, {93, 533}, {76, 94}));

#endif

	SpriteRenderer renderer(Shader("../shaders/simple_tex.vs", "../shaders/simple_tex.fs"));

	double frametime = 0;
	double lastsecond = 0;
	double lastframetime = 0;
	float delta = 0;
	int fps = 0;

	double lastframe = 0;
	int frame = 0;

	while (!display.shouldClose()) {
		frametime = glfwGetTime();
		delta = static_cast<float>(frametime - lastframetime);
		lastframetime = frametime;

		display.clear(0.25f, 0.25f, 0.85f, 1);


		const float speed = 15.0f * delta;

		if (Keyboard::isKeyPressed(GLFW_KEY_W)) {
			quads[0].setPosition(quads[0].getPosition() - Vec2f(0, speed));
		} else if (Keyboard::isKeyPressed(GLFW_KEY_S)) {
			quads[0].setPosition(quads[0].getPosition() + Vec2f(0, speed));
		}

		if (Keyboard::isKeyPressed(GLFW_KEY_D)) {
			quads[0].setPosition(quads[0].getPosition() + Vec2f(speed, 0));
		} else if (Keyboard::isKeyPressed(GLFW_KEY_A)) {
			quads[0].setPosition(quads[0].getPosition() - Vec2f(speed, 0));
		}
	

#ifdef RUNNER
		if ((frametime - lastframe) > 0.05f) {
			if (++frame > 12)
				frame = 5;
			lastframe = frametime;
		}

#elif defined(VEGETA)

		if ((frametime - lastframe) > 0.1f) {
			if (++frame > 1)
				frame = 0;
			lastframe = frametime;
		}


#endif

		renderer.submit(&quads[frame], 1);
		renderer.flush();
		display.update();



		++fps;
		if ((frametime - lastsecond) >= 1.0f) {
			std::cout << "FPS: " << fps << '\n' << 
				  "QUAD POS:\n" << 
				  "X: " << quads[0].getPosition().x << '\n' <<
			          "Y: " << quads[0].getPosition().y << '\n';
			
			fps = 0;
			lastsecond = frametime;
		}
	}
}


int main()
{
	try  {
		game_main();
		return EXIT_SUCCESS;
	} catch (std::exception& exception) {
		std::cerr << "FATAL EXCEPTION: " << exception.what() << '\n';
	} catch (...) {
		std::cerr << "FATAL UNKNOWN EXCEPTION...\n"; 
	}

	return EXIT_FAILURE;
}

