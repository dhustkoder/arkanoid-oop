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


void game_main()
{
	using namespace gp;

	constexpr const int kWinWidth = 944;
	constexpr const int kWinHeight = 531;

	Display display("Hello GProj", kWinWidth, kWinHeight);
	display.setVsync(false);

	Texture sheet_tex("vegeta.png");

	Sprite pirate({8,4.5f}, {1, 2}, 593, 654, 192, 288, {1, 1, 1, 1}, sheet_tex);
	Sprite bunny({8,4.5f}, {1, 2}, 661, 722, 192, 288, {1, 1, 1, 1}, sheet_tex);
	std::vector<Sprite> quads { pirate, bunny };


	SpriteRenderer renderer(Shader("../shaders/simple_tex.vs", "../shaders/simple_tex.fs"));

	double frametime = 0;
	double lastframe = 0;
	double lastsecond = 0;
	double lastframetime = 0;
	float delta = 0;
	int fps = 0;
	int frame = 0;

	while (!display.shouldClose()) {
		frametime = glfwGetTime();
		delta = static_cast<float>(frametime - lastframetime);
		lastframetime = frametime;

		display.clear(0.25f, 0.25f, 0.85f, 1);


		const float speed = 5.0f * delta;
		if (Keyboard::isKeyPressed(GLFW_KEY_W)) {
			quads[0].setPosition(quads[0].getPosition() + glm::vec2(0, speed));
		} else if (Keyboard::isKeyPressed(GLFW_KEY_S)) {
			quads[0].setPosition(quads[0].getPosition() - glm::vec2(0, speed));
		}

		if (Keyboard::isKeyPressed(GLFW_KEY_D)) {
			quads[0].setPosition(quads[0].getPosition() + glm::vec2(speed, 0));
		} else if (Keyboard::isKeyPressed(GLFW_KEY_A)) {
			quads[0].setPosition(quads[0].getPosition() - glm::vec2(speed, 0));
		}

		renderer.submit(&quads[frame], 1);

		if ((frametime - lastframe) >= 0.1f) {
			lastframe = frametime;
			if (++frame > 1)
				frame = 0;
		}

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

