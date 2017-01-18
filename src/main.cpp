#include <stdlib.h>
#include <stdio.h>
#include "display.hpp"
#include "renderer.hpp"
#include "finally.hpp"
#include "matrix4.hpp"

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

	set_vsync(true);
	bind_shader(0);
	bind_texture(0);

	constexpr const Vertex vertices[4] {
		{ { 0.5f,  0.5f }, { 1, 0 }, { 1, 0, 0, 1 } },
		{ { 0.5f, -0.5f }, { 1, 1 }, { 0, 1, 0, 1 } },
		{ {-0.5f, -0.5f }, { 0, 1 }, { 0, 0, 1, 1 } },
		{ {-0.5f,  0.5f }, { 0, 0 }, { 1, 1, 0, 1 } }
	};

	constexpr const GLuint indices[6] {
		0, 1, 3,
		1, 2, 3
	};

	const Elements elements {
		{ vertices, sizeof(vertices)/sizeof(vertices[0]) },
		{ indices, sizeof(indices)/sizeof(indices[0]) }
	};


	while (update_display()) {
		const auto time = static_cast<float>(glfwGetTime());
		Mat4 trans = identity_mat4();
		trans = scale(trans, {0.5f, 0.5f, 0});
		trans = translate(trans, {0.5f, -0.5f, 0.0f});
		trans = rotate(trans, (kPI * -0.2f) * time, {0, 0, 1});
		set_uniform(0, trans, "transform");
		clear_display({0, 0, 0, 1});
		draw(GL_TRIANGLES, elements);
	}


	return EXIT_SUCCESS;
}


bool initialize_systems()
{
	const char* const vertexfiles[1] { "../shaders/vertex.glsl" };
	const char* const fragmentfiles[1] { "../shaders/fragment.glsl" };
	const char* const texturefiles[1] { "container.jpg" };
	
	const gp::ShadersProgramsFiles shaders {
		vertexfiles,
		fragmentfiles,
		1
	};

	const gp::TexturesFiles textures {
		texturefiles,
		1
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

