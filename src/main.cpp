#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "finally.hpp"
#include "display.hpp"
#include "meshes.hpp"
#include "shaders.hpp"


int main(int /*argc*/, char** /*argv*/)
{
	using namespace gp;

	Display* const display = 
	  create_display("Hello gproj!", 800, 600);

	if (display == nullptr)
		return EXIT_FAILURE;

	const auto display_guard = finally([display] {
		destroy_display(display);
	});

	Vertex vertices[] = {
		{-0.5f, -0.5f, 0},
		{0, 0.5f, 0},
		{0.5f, -0.5f, 0}
	};
	

	Shaders* const shaders = create_shaders();
	if (shaders == nullptr)
		return EXIT_FAILURE;

	const auto shaders_guard = finally([shaders] {
		destroy_shaders(shaders);
	});

	Meshes* const meshes = create_meshes(&vertices[0], 1, 3);

	if (meshes == nullptr)
		return EXIT_FAILURE;

	const auto meshes_guard = finally([meshes] {
		destroy_meshes(meshes);
	});

	// just show to the screen
	long fps = 0;
	clock_t start_time = time(nullptr);;
	while (update_display(display)) {
		clear_display(0, 0.5f, 0.3f, 1, display);
		bind_shaders(*shaders);
		draw_meshes(*meshes);


		++fps;
		if ((time(nullptr) - start_time) >= 1) {
			printf("FPS: %ld\n", fps);
			fps = 0;
			start_time = time(nullptr);
		}
	};

	return EXIT_SUCCESS;
}



