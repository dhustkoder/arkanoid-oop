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

	constexpr const int kWinWidth = 1366;
	constexpr const int kWinHeight = 766;

	Display display("Hello GProj", kWinWidth, kWinHeight);
	display.setVsync(false);

	Texture sheet_tex("../sheet.png");

	Sprite pirate({8,4.5f}, {0.8f, 0.8f}, {0.0f, 0.0f}, {0.19f, 0.41f}, {1, 1, 1, 1}, sheet_tex);
	Sprite bunny({8,4.5f}, {0.8f, 0.8f}, {0.21f, 0.0f}, {0.22f, 0.41f}, {1, 1, 1, 1},  sheet_tex);
	std::vector<Sprite> quads;
	quads.reserve(50);
	
	float posx = 2.0f;
	float posy = 7.0f;
	for (int i = 0; i < 10000; ++i) {
		Sprite sprite = (rand() % 2) == 0 ? pirate : bunny;

		if (posx >= 15.0f) {
			posx = 2.0f;
			posy -= 2.0f;
			if (posy <= 1.0f)
				posy = 7.0f;
		}

		sprite.setPosition({posx, posy});
		quads.emplace_back(sprite);

		posx += 2.0f;
	}


	SpriteRenderer renderer(Shader("../shaders/simple_tex.vs", "../shaders/simple_tex.fs"));

	double frametime = 0;
	double lastsecond = 0;
	double lastframetime = 0;
	float delta = 0;
	int fps = 0;


	while (!display.shouldClose()) {
		frametime = glfwGetTime();
		delta = static_cast<float>(frametime - lastframetime);
		lastframetime = frametime;

		display.clear(1.0f, 0.0f, 1.0f, 1);


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


		if (quads[0].getTop() >= quads[1].getBottom() &&
		    quads[0].getBottom() <= quads[1].getTop() &&
		    quads[0].getRight() >= quads[1].getLeft() &&
		    quads[0].getLeft() <= quads[1].getRight()) {
			quads[1].setColor({sinf(frametime), cosf(frametime), sinf(lastframetime), cosf(frametime) + 1.0f});
		}

		renderer.submit(quads.data(), quads.size());
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

