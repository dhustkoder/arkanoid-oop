#include <stdlib.h>
#include <stdio.h>
#include "finally.hpp"
#include "display.hpp"
#include "renderer.hpp"
#include "shader.hpp"

static bool initialize_systems();
static void terminate_systems();


int main(int /*argc*/, char** /*argv*/)
{
	using namespace gp;
	if (!initialize_systems())
		return EXIT_FAILURE;
	const auto systems_terminator = finally([] {
		terminate_systems();
	});


	Vec2 positions[] { { 0, 0 }, { -0.8f, 0.8f } };
	Vec2 sizes[] { { 0.4f, 0.4f }, { 0.2f, 0.2f } };
	Color clear_colors[] { { 1, 1, 1, 1 }, { 1, 1, 1, 1 } };
	bool dynamics[] { true, true };

	const auto sprites_ids = add_sprites(positions, sizes, clear_colors, dynamics, 2);

	add_keycallback(&clear_colors, [](void* const userdata, int key) {

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
		clear_display({0, 0, 0, 1});
		draw_sprites();
	}

	return EXIT_SUCCESS;
}

bool initialize_systems()
{
	if (!gp::initialize_display("Hello GProj", 800, 600) || 
	    !gp::initialize_renderer() /*||
	    !gp::initialize_shader()*/) {
		terminate_systems();
		return false;
	}

	return true;
}

void terminate_systems()
{
	gp::terminate_renderer();
	gp::terminate_display();
	//gp::terminate_shader();
}

