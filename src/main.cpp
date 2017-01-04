#include <stdlib.h>
#include <stdio.h>
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


	const std::vector<Vec3f> verts {
		{  0.5f,  0.5f,  0.0f }, // top right
		{  0.5f, -0.5f,  0.0f }, // bottom right
		{ -0.5f, -0.5f,  0.0f }, // bottom left
		{ -0.5f,  0.5f,  0.0f }  // top left
	};

	const std::vector<GLuint> inds {
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (update_display()) {
		clear_display({0, 0, 0, 1});
		draw(GL_TRIANGLES, verts, inds);
	}

	return EXIT_SUCCESS;
}

bool initialize_systems()
{
	if (!gp::initialize_display("Hello GProj", 800, 600) || 
	    !gp::initialize_renderer() ||
	    !gp::initialize_shader()) {
		terminate_systems();
		return false;
	}

	return true;
}

void terminate_systems()
{
	gp::terminate_renderer();
	gp::terminate_display();
	gp::terminate_shader();
}

