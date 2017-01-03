#include <stdlib.h>
#include <stdio.h>
#include "finally.hpp"
#include "display.hpp"


namespace gp {
	extern Color clear_color;
}


int main(int /*argc*/, char** /*argv*/)
{
	using namespace gp;

	if (init_display("Hello GProj", 800, 600) == false)
		return EXIT_FAILURE;

	while (update_display()) {
		clear_display(clear_color);
	}

	const auto display_guard = finally([] {
		close_display();
	});

	return EXIT_SUCCESS;
}



