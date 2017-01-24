#include <stdio.h>
#include "renderer/renderer.hpp"
#include "utils/finally.hpp"
#include "display.hpp"

namespace gp {

GLFWwindow* window = nullptr;
bool keystate[1024] { false };

bool create_display(const char* title, int w, int h);
static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);

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

	glfwSetKeyCallback(window, &key_callback);
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


void key_callback(GLFWwindow* const win,
                       const int key,
                       const int /*scancode*/,
                       const int action,
                       const int /*mods*/)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(win, GLFW_TRUE);
	} else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		static bool wireframe_on = false;
		wireframe_on = !wireframe_on;
		set_wireframe_mode(wireframe_on);
	} else {
		keystate[key] = action != GLFW_RELEASE;
	}
}


} // namespace gp

