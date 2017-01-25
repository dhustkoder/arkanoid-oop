#include <stdio.h>
#include "renderer/renderer.hpp"
#include "utils/finally.hpp"
#include "display.hpp"

namespace gp {

GLFWwindow* window = nullptr;


extern void kbd_callback(GLFWwindow* const win, int key, int scancode, int action, int mods);


bool create_display(const char* title, int w, int h);
static void error_callback(int error, const char* description);


bool create_display(const char* const title, const int w, const int h)
{
	GLenum errcode;

	glfwSetErrorCallback(&error_callback);

	if (glfwInit() != GLFW_TRUE)
		return false;

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(w, h, title, NULL, NULL);

	if (window == nullptr)
		return false;

	glfwSetKeyCallback(window, &kbd_callback);
	glfwMakeContextCurrent(window);

	if ((errcode = glewInit()) != GLEW_OK) {
		fprintf(stderr, "%s\n", glewGetErrorString(errcode));
		return false;
	}


	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return true;
}


void free_display()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	window = nullptr;
}


void error_callback(const int error, const char* const description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}


} // namespace gp

