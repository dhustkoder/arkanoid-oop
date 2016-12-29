#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "display.hpp"
#include "meshes.hpp"
#include "finally.hpp"


int main(int /*argc*/, char** /*argv*/)
{
	gp::Display* const display = 
	  gp::create_display("Hello gproj!", 800, 600);

	if (display == nullptr)
		return EXIT_FAILURE;

	const auto display_guard = gp::finally([display] {
		gp::destroy_display(display);
	});

	gp::Vertex vertices[] = {
		{-0.9f, -0.9f, 0},
		{0, 0.9f, 0},
		{0.9f, -0.9f, 0}
	};
	
	gp::Meshes* const meshes = gp::create_meshes(&vertices[0], 1, 3);

	if (meshes == nullptr)
		return EXIT_FAILURE;

	const auto meshes_guard = gp::finally([meshes] {
		destroy_meshes(meshes);
	});

	// draw both buffers
	for (int i = 0; i < 2; ++i) {
		gp::clear_display(0, 0.5f, 0.3f, 1, display);
		gp::draw_meshes(*meshes);
		gp::update_display(display);
	}

	// just show to the screen
	long fps = 0;
	clock_t start_time = time(nullptr);;
	while (update_display(display)) {
		++fps;
		if ((time(nullptr) - start_time) >= 1) {
			printf("FPS: %ld\n", fps);
			fps = 0;
			start_time = time(nullptr);
		}
	};

	return EXIT_SUCCESS;
}



