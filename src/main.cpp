#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "display.hpp"
#include "meshes.hpp"

int main(int /*argc*/, char** /*argv*/)
{
	int ret = EXIT_SUCCESS;

	gp::Display* const display = 
	  gp::create_display("Hello gproj!", 800, 600);

	if (display == nullptr)
		return EXIT_FAILURE;

	gp::Vertex vertices[] = {
		{-0.9f, -0.9f, 0},
		{0, 0.9f, 0},
		{0.9f, -0.9f, 0}
	};
	
	gp::Meshes* const meshes = gp::create_meshes(&vertices[0], 1, 3);

	if (meshes == nullptr) {
		ret = EXIT_FAILURE;
		goto free_display;
	}

	// draw both buffers
	for (int i = 0; i < 2; ++i) {
		gp::clear_display(0, 0.5f, 0.3f, 1, display);
		gp::draw_meshes(*meshes);
		gp::update_display(display);
	}

	// just show to the screen
	long fps = 0;
	auto start_clocks = clock();
	while (update_display(display)) {
		++fps;
		if ((clock() - start_clocks) > CLOCKS_PER_SEC) {
			printf("FPS: %ld\n", fps);
			fps = 0;
			start_clocks = clock();
		}
	};


	gp::destroy_meshes(meshes);
free_display:
	gp::destroy_display(display);
	return ret;
}



