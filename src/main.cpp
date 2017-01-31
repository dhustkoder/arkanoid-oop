#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "exception.hpp"
#include "display.hpp"
#include "keyboard.hpp"
#include "shader.hpp"
#include "renderable2D.hpp"
#include "batch_renderer2D.hpp"

void game_main()
{
	using namespace gp;

	constexpr const int kWinWidth = 960;
	constexpr const int kWinHeight = 540;
	
	Display display("Hello GProj", kWinWidth, kWinHeight);
	Shader shader("../shaders/simple.vs", "../shaders/simple.fs");
	shader.enable();
	const glm::mat4 projection = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	shader.setUniformMat4("projection", projection);

	Renderable2D quads[] {
		{ { 5, 5 }, { 1, 1 }, { 1, 0, 1, 1 } },
		{ { 7, 1 }, { 2, 3 }, {0.2f, 0, 1, 1} }
	};

	BatchRenderer2D renderer;

	double frametime = glfwGetTime();
	double lastsecond = frametime;
	double lastframetime = frametime;
	float delta;
	int fps = 0;

	while (!display.shouldClose()) {
		frametime = glfwGetTime();
		delta = static_cast<float>(frametime - lastframetime);
		lastframetime = frametime;
		display.clear(0.4f, 0, 0, 1);


		if (Keyboard::isKeyPressed(GLFW_KEY_W)) {
			quads[0].setPosition(quads[0].getPosition() + glm::vec2(0, 1.0f * delta));
		} else if (Keyboard::isKeyPressed(GLFW_KEY_S)) {
			quads[0].setPosition(quads[0].getPosition() - glm::vec2(0, 1.0f * delta));
		}

		if (Keyboard::isKeyPressed(GLFW_KEY_D)) {
			quads[0].setPosition(quads[0].getPosition() + glm::vec2(1.0f * delta, 0));
		} else if (Keyboard::isKeyPressed(GLFW_KEY_A)) {
			quads[0].setPosition(quads[0].getPosition() - glm::vec2(1.0f * delta, 0));
		}

		renderer.submit(&quads[0], sizeof(quads) / sizeof(quads[0]));
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
	} catch (gp::Exception& exception) {
		std::cerr << exception.what() << '\n';
	} catch (...) {
		std::cerr << "Unknown exception...\n";
	}

	return EXIT_FAILURE;
}

