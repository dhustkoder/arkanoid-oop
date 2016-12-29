#include <stdio.h>
#include "display.hpp"

namespace gp {

static Display s_display;

Display* create_display(const char* const title, const int w, const int h)
{
	GLenum glew_ret;

	if (glfwInit() == 0) {
		fprintf(stderr, "Couldn't initialize %s\n", "glfw");
		return nullptr;
	}

	GLFWwindow* const window = glfwCreateWindow(w, h, title, NULL, NULL);
	if (window == nullptr)
		goto free_glfw;

	
	glfwMakeContextCurrent(window);

	glew_ret = glewInit();
	if (glew_ret != GLEW_OK) {
		fprintf(stderr, "%s\n", glewGetErrorString(glew_ret));
		goto free_window;
	}

	s_display = { window };
	clear_display(0, 0, 0, 1, &s_display);
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


bool update_display(Display* const display)
{
	glfwPollEvents();
	glfwSwapBuffers(display->window);
	return glfwWindowShouldClose(display->window) == 0;
}


} // namespace gp

