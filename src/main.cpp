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

/*
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
*/

	const std::vector<Vec3f> t0 {
		{ -0.4f,  0.0f,  0.0f },
		{ -0.8f, -0.4f,  0.0f },
		{  0.0f, -0.4f,  0.0f },

		{  0.4f,  0.0f,  0.0f },
		{  0.0f, -0.4f,  0.0f },
		{  0.8f, -0.4f,  0.0f },

		{  0.0f,  0.4f,  0.0f },
		{ -0.4f,  0.0f,  0.0f },
		{  0.4f,  0.0f,  0.0f }

	};

	Vec4f t0_color { 1, 1, 0, 1 };

	bool wireframe = false;
	add_keycallback(&wireframe,
	[](void* userdata, const int key, const int action) {
		bool& wireframe_on = *reinterpret_cast<bool*>(userdata);
		if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
			wireframe_on = !wireframe_on;
			set_wireframe_mode(wireframe_on);
		}
	});

	while (update_display()) {
		clear_display({0, 0, 0, 1});
		const auto time = glfwGetTime();
		t0_color.r = static_cast<GLfloat>((cosl(time) / 2) + 0.5f);
		t0_color.g = static_cast<GLfloat>((sinl(time) / 2) + 0.5f);
		t0_color.b = static_cast<GLfloat>((tanl(time) / 2) + 0.5f);
		set_shader_uniform("uni_color", t0_color);
		draw_arrays(GL_TRIANGLES, t0);
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

