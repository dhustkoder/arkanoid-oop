#include <stdlib.h>
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

	do {
		gp::clear_display(0, 0.5f, 1, 1, display);
		gp::draw_meshes(*meshes);
	} while (update_display(display));


	gp::destroy_meshes(meshes);
free_display:
	gp::destroy_display(display);
	return ret;
}



