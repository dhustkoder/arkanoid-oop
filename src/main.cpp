#include <iostream>
#include "display.hpp"
#include "keyboard.hpp"
#include "shader.hpp"
#include "exception.hpp"


int game_main()
{
	gp::Display display("Hello GProj", 800, 600);
	gp::Shader shader("../shaders/simple.vs", "../shaders/simple.fs");
	shader.enable();

	while (!display.shouldClose()) {
		display.clear(0.4f, 0, 0, 1);
		display.update();
	}

	return EXIT_SUCCESS;
}


int main()
{
	try  {
		int exitcode = game_main();
		return exitcode;
	} catch (gp::Exception& exception) {
		std::cerr << exception.what() << '\n';
	} catch (...) {
		std::cerr << "Unknown exception...\n";
	}

	return EXIT_FAILURE;
}

