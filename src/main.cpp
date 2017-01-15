#include <stdlib.h>
#include <stdio.h>
#include "display.hpp"
#include "renderer.hpp"
#include "finally.hpp"
#include "matrix4.hpp"
#include "vector4.hpp"

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

	bind_shader(0);
	bind_texture(0);

	bool wireframe = false;
	add_keycallback(&wireframe,
	[](void* userdata, const int key, const int action) {
		bool& wireframe_on = *reinterpret_cast<bool*>(userdata);
		if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
			wireframe_on = !wireframe_on;
			set_wireframe_mode(wireframe_on);
		}
	});

	std::vector<Vertex> vertices {
		{ { 0.5f,  0.5f }, { 1, 1 }, { 1, 0, 0, 1 } },
		{ { 0.5f, -0.5f }, { 1, 0 }, { 0, 1, 0, 1 } },
		{ {-0.5f, -0.5f }, { 0, 0 }, { 0, 0, 1, 1 } },
		{ {-0.5f,  0.5f }, { 0, 1 }, { 1, 1, 0, 1 } }
	};

	std::vector<GLuint> indices {
		0, 1, 3,
		1, 2, 3
	};

	Mat4 identity {{
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	}};

	const Elements elements {
		{ &vertices[0], (long)vertices.size() },
		{ &indices[0], (long)indices.size() }
	};


	set_uniform(0, identity, "transform");

	while (update_display()) {
		clear_display({0, 0, 0, 1});
		draw(GL_TRIANGLES, elements);
	}

	return EXIT_SUCCESS;

}


bool initialize_systems()
{
	const std::vector<std::pair<std::string, std::string>> shaders {
		{ "../shaders/vertex.glsl", "../shaders/fragment.glsl" }
	};

	const std::vector<std::string> textures {
		"container.jpg"
	};

	if (!gp::initialize_display("Hello GProj", 800, 600))
		goto display_failed;
	if (!gp::initialize_renderer(textures, shaders))
		goto renderer_failed;

	return true;

renderer_failed:
	gp::terminate_display();
display_failed:
	return false;
}


void terminate_systems()
{
	gp::terminate_renderer();
	gp::terminate_display();
}

