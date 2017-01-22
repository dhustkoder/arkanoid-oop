#include <stdio.h>
#include "renderer/renderer.hpp"
#include "utils/finally.hpp"
#include "display.hpp"

namespace gp {

GLFWwindow* window = nullptr;
bool keystate[1024] { false };

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);

bool initialize_display(const char* const title, const int w, const int h)
{
	constexpr const int infosize = 4;

	constexpr GLenum infonums[infosize] {
		GL_VENDOR, GL_RENDERER, GL_VERSION,
		GL_SHADING_LANGUAGE_VERSION
	};

	constexpr const char* const infostrs[infosize] {
		"VENDOR", "RENDERER", "VERSION",
		"SHADING LANGUAGE VERSION"
	};

	GLenum errcode;

	glfwSetErrorCallback(&error_callback);

	if (glfwInit() != GLFW_TRUE)
		return false;

	auto failure_guard = finally([] {
		terminate_display();
	});

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

	puts("OpenGL");
	for (int i = 0; i < infosize; ++i)
		printf("%s: %s\n", infostrs[i], glGetString(infonums[i]));


	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glViewport(0, 0, w, h);
	glEnable(GL_DEPTH_TEST);
	failure_guard.Abort();
	return true;
}


void terminate_display()
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

