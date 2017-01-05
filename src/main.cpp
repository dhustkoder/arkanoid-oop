#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
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


	bool wireframe = false;
	add_keycallback(&wireframe,
	[](void* userdata, const int key, const int action) {
		bool& wireframe_on = *reinterpret_cast<bool*>(userdata);
		if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
			wireframe_on = !wireframe_on;
			set_wireframe_mode(wireframe_on);
		}
	});


	std::vector<Vertex> triangle {
		{{  0.0f,  0.4f,  0.0f }, { 1, 0, 0, 1 }},
		{{  0.4f,  0.0f,  0.0f }, { 0, 1, 0, 1 }},
		{{ -0.4f,  0.0f,  0.0f }, { 0, 0, 1, 1 }}
	};

	while (update_display()) {
		clear_display({0, 0, 0, 1});
		draw_arrays(GL_TRIANGLES, triangle);
	}

	return EXIT_SUCCESS;
}


bool initialize_systems()
{
	const std::vector<std::pair<std::string, std::string>> shaders {
		{ "shaders/vertex.glsl", "shaders/fragment.glsl" }
	};

	if (!gp::initialize_display("Hello GProj", 800, 600) || 
	    !gp::initialize_renderer() ||
	    !gp::initialize_shader(shaders)) {
		terminate_systems();
		return false;
	}

	gp::bind_shader_program(0);
	return true;
}


void terminate_systems()
{
	gp::terminate_renderer();
	gp::terminate_display();
	gp::terminate_shader();
}

