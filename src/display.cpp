#include <stdio.h>
#include "display.hpp"

namespace gp {

static Display s_display;

Display* create_display(const char* const title, const int w, const int h)
{
	if (!glfwInit())
		return nullptr;

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* const window = glfwCreateWindow(w, h, title, NULL, NULL);
	if (window == nullptr)
		goto free_glfw;

	glfwMakeContextCurrent(window);
	s_display = { window };
	return &s_display;

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
	glfwSwapBuffers(display->window);
	glfwPollEvents();
	return glfwWindowShouldClose(display->window) == 0;
}


} // namespace gp

