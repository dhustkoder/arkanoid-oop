#include <iostream>
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

	constexpr const int kWinWidth = 768;
	constexpr const int kWinHeight = 432;

	Display display("Hello GProj", kWinWidth, kWinHeight);

	Sprite quads[] {
		{ { 5.0f, 5.0f }, { 1, 1 }, { 1, 1, 1, 1 }, 0 },
		{ { 8.0f, 4.5f }, { 1, 1 }, { 1, 1, 1, 1 }, 1 }
	};

	std::vector<Texture> textures;
	textures.emplace_back("../dragon.png");
	textures.emplace_back("../snowman.png");

	SpriteRenderer renderer(Shader("../shaders/simple_tex.vs", "../shaders/simple_tex.fs"), std::move(textures));

	double frametime = glfwGetTime();
	double lastsecond = frametime;
	double lastframetime = frametime;
	float delta;
	int fps = 0;

	while (!display.shouldClose()) {
		frametime = glfwGetTime();
		delta = static_cast<float>(frametime - lastframetime);
		lastframetime = frametime;
		display.clear(0.25f, 0.25f, 0.95f, 1);


		if (Keyboard::isKeyPressed(GLFW_KEY_W)) {
			quads[0].setPosition(quads[0].getPosition() + glm::vec2(0, 5.0f * delta));
		} else if (Keyboard::isKeyPressed(GLFW_KEY_S)) {
			quads[0].setPosition(quads[0].getPosition() - glm::vec2(0, 5.0f * delta));
		}

		if (Keyboard::isKeyPressed(GLFW_KEY_D)) {
			quads[0].setPosition(quads[0].getPosition() + glm::vec2(5.0f * delta, 0));
		} else if (Keyboard::isKeyPressed(GLFW_KEY_A)) {
			quads[0].setPosition(quads[0].getPosition() - glm::vec2(5.0f * delta, 0));
		}

		if (quads[0].getTop() >= quads[1].getBottom() &&
		    quads[0].getBottom() <= quads[1].getTop() &&
		    quads[0].getRight() >= quads[1].getLeft() &&
		    quads[0].getLeft() <= quads[1].getRight()) {
			quads[1].setColor({sinf(frametime), cosf(frametime), sinf(lastframetime), cosf(frametime) + 1.0f});
		}

		renderer.submit(&quads[0], sizeof(quads) / sizeof(quads[0]));
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

