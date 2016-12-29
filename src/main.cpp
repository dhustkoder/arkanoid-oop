#include <stdlib.h>
#include "display.hpp"

int main(int /*argc*/, char** /*argv*/)
{
	gp::Display* const display = 
	  gp::create_display("Hello gproj!", 800, 600);

	if (display == nullptr)
		return EXIT_FAILURE;

	while (update_display(display)) {
		gp::clear_display(0, 0.5f, 1, 1, display);
	}

	gp::destroy_display(display);
	return EXIT_SUCCESS;
}



