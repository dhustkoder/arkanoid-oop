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
#include "ball.hpp"


void game_main()
{
	using namespace gp;

	constexpr const int kWinWidth = 800;
	constexpr const int kWinHeight = 600;

	Display display("Hello GProj", kWinWidth, kWinHeight);
	display.setVsync(false);
	SpriteRenderer renderer(Shader("../shaders/simple_tex.vs", "../shaders/simple_tex.fs"));


	const Texture spritesheet("../spritesheet.png");
	Ball ball(spritesheet, {400, 300}, 100.0f, 50.0f, {0, 80}, {24, 24});
	Sprite square(spritesheet, {400, 300}, {65, 32}, {0, 0}, {65, 32});

	double frametime = 0;
	double lastframetime = 0;
	double lastsecond = 0;
	float delta;
	int fps = 0;

	while (!display.shouldClose()) {
		frametime = glfwGetTime();
		delta = static_cast<float>(frametime - lastframetime);
		lastframetime = frametime;
		display.clear(0.25f, 0.25f, 0.85f, 1);

		ball.update(delta);

		renderer.submit(&ball, 1);
		renderer.submit(&square, 1);
		renderer.flush();
		display.update();


		++fps;
		if ((frametime - lastsecond) >= 1.0f) {
			std::cout << "FPS: " << fps << '\n';
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

