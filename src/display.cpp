#include <stdio.h>
#include "display.hpp"

namespace gp {

static Display s_display;

Display* create_display(const char* const title, const int w, const int h)
{
	constexpr const auto infosize = 4;
	constexpr GLenum infonums[infosize] {
		GL_VENDOR, GL_RENDERER, GL_VERSION,
		GL_SHADING_LANGUAGE_VERSION
	};
	constexpr const char* const infostrs[infosize] {
		"VENDOR", "RENDERER", "VERSION",
		"SHADING LANGUAGE VERSION"
	};

	GLenum glew_ret;
	GLFWwindow* window;

	if (glfwInit() == 0) {
		fprintf(stderr, "Couldn't initialize %s\n", "glfw");
		return nullptr;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(w, h, title, NULL, NULL);

	if (window == nullptr)
		goto free_glfw;
	
	glfwMakeContextCurrent(window);

	glew_ret = glewInit();
	if (glew_ret != GLEW_OK) {
		fprintf(stderr, "%s\n", glewGetErrorString(glew_ret));
		goto free_window;
	}

	puts("OpenGL");
	for (size_t i = 0; i < infosize; ++i)
		printf("%s: %s\n", infostrs[i], glGetString(infonums[i]));

	s_display = { window };
	glfwSwapInterval(0);
	return &s_display;

free_window:
	glfwDestroyWindow(window);
free_glfw:
	glfwTerminate();
	return nullptr;
}


void destroy_display(Display* const display)
{
	glfwDestroyWindow(display->window);
	glfwTerminate();
}




} // namespace gp

