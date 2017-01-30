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

	const Renderable2D quad({5, 5}, {1.0f, 1.0f}, {1, 0, 1, 1});
	const Renderable2D quad2({7, 1}, {2, 3}, {0.2f, 0, 1, 1});
	BatchRenderer2D renderer;

	double frametime;
	double lastsecond = glfwGetTime();
	int fps = 0;

	while (!display.shouldClose()) {
		frametime = static_cast<float>(glfwGetTime());
		display.clear(0.4f, 0, 0, 1);

		renderer.begin();
		renderer.submit(&quad);
		renderer.submit(&quad2);
		renderer.end();
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

