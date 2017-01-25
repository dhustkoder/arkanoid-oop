#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "platform/display.hpp"
#include "platform/kbd_mouse_input.hpp"
#include "renderer/renderer.hpp"
#include "renderer/shaders.hpp"
#include "renderer/camera.hpp"
#include "utils/finally.hpp"
#include "math/matrix4.hpp"
#include "math/vector2.hpp"


constexpr const char* kWinTitle = "GProj";
constexpr const int kWinWidth = 480;
constexpr const int kWinHeight = 360;


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

	set_vsync(false);
	
	bind_shader(0);
	
	set_shader_model(translate(identity_mat4(), {0, 0, 0}));
	reset_camera(kWinWidth, kWinHeight, 3.0f, 0.25f, { 0, 0, 4 }, { 0, 1, 0 });

	constexpr const Vertex data[] {
		{ { 0.5f, 0.5f, 0.0f } },
		{ { 0.5f,-0.5f, 0.0f } },
		{ {-0.5f,-0.5f, 0.0f } },
		{ {-0.5f, 0.5f, 0.0f } },

		{ { 0.5f, 0.5f,-1.0f } },
		{ { 0.5f,-0.5f,-1.0f } },
		{ {-0.5f,-0.5f,-1.0f } },
		{ {-0.5f, 0.5f,-1.0f } }
	};

	const unsigned int indices[] {
		0, 1, 3,
		2, 1, 3,
		
		4, 7, 3,
		0, 4, 3


	};

	const Elements elements {
		{ &data[0], sizeof(data)/sizeof(data[0]) },
		{ &indices[0], sizeof(indices)/sizeof(indices[0]) }
	};

	int vbo = register_element_buffer(elements);
	bind_element_buffer(vbo);

	time_t clk = time(nullptr);
	long fps = 0;
	float lastframe = 0;
	float delta;


	while (update_display()) {
		clear_screen({ 0, 0, 0, 1 });
		const float frametime = glfwGetTime();
		delta = frametime - lastframe;
		lastframe = frametime;

		update_camera(delta);
		
		draw_element_buffer(GL_TRIANGLES, 0, elements.indices.count);

		++fps;
		time_t clk_end = time(nullptr);
		if ((clk_end - clk) >= 1) {
			printf("FPS: %ld\n", fps);
			fps = 0;
			clk = clk_end;
		}
	}

	return EXIT_SUCCESS;
}


bool initialize_systems()
{
	constexpr const char* const vertexfiles[1] { 
		"../shaders/simple.vs"
	};

	constexpr const char* const fragmentfiles[1] {
		"../shaders/simple.fs"
	};
	
	const gp::ShadersProgramsFiles shaders {
		vertexfiles,
		fragmentfiles,
		1
	};

	const gp::TexturesFiles textures {
		nullptr,
		0
	};

	if (!gp::initialize_renderer(kWinTitle, kWinWidth, kWinHeight, textures, shaders))
		goto renderer_failed;

	return true;

renderer_failed:
	return false;
}


void terminate_systems()
{
	gp::terminate_renderer();
}

