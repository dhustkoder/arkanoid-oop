#include <stdlib.h>
#include <stdio.h>
#include "finally.hpp"
#include "display.hpp"


int main(int /*argc*/, char** /*argv*/)
{
	using namespace gp;

	if (!init_display("Hello GProj", 800, 600))
		return EXIT_FAILURE;
	const auto display_guard = finally([] {
		close_display();
	});


	Color clear_color { 0.0f, 0.0f, 0.0f, 1.0f };

	add_keycallback(&clear_color, [](void* const userdata, int key) {
		auto& color = *reinterpret_cast<Color*>(userdata);

		const auto inc = [] (float& col) {
			if (col < 1.0f)
				col += 0.10f;
		};
		const auto dec = [] (float& col) {
			if (col > 0.0f)
				col -= 0.10f;
		};

		switch (key) {
		case GLFW_KEY_UP: inc(color.r); break;
		case GLFW_KEY_DOWN: dec(color.r); break;
		case GLFW_KEY_RIGHT: inc(color.g); break;
		case GLFW_KEY_LEFT: dec(color.g); break;
		case GLFW_KEY_ENTER: inc(color.b); break;
		case GLFW_KEY_BACKSPACE: dec(color.b); break;
		}
	});

	while (update_display()) {
		clear_display(clear_color);
	}

	return EXIT_SUCCESS;
}



