#include <stdio.h>
#include "display.hpp"
#include "renderer.hpp"
#include "finally.hpp"

namespace gp {

GLFWwindow* glfw_window = nullptr;

static void glfw_error_callback(int error, const char* description);
static void glfw_key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);


bool initialize_display(const char* const title, const int w, const int h)
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

	GLenum errcode;

	glfwSetErrorCallback(&glfw_error_callback);

	if (glfwInit() != GLFW_TRUE)
		return false;

	auto failure_guard = finally([] {
		terminate_display();
	});

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfw_window = glfwCreateWindow(w, h, title, NULL, NULL);

	if (glfw_window == nullptr)
		return false;

	glfwSetKeyCallback(glfw_window, &glfw_key_callback);
	glfwMakeContextCurrent(glfw_window);

	if ((errcode = glewInit()) != GLEW_OK) {
		fprintf(stderr, "%s\n", glewGetErrorString(errcode));
		return false;
	}

	glViewport(0, 0, w, h);

	puts("OpenGL");
	for (int i = 0; i < infosize; ++i)
		printf("%s: %s\n", infostrs[i], glGetString(infonums[i]));

	failure_guard.Abort();
	return true;
}


void terminate_display()
{
	glfwDestroyWindow(glfw_window);
	glfwTerminate();
	glfw_window = nullptr;
}


void glfw_error_callback(const int error, const char* const description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}


void glfw_key_callback(GLFWwindow* const win,
                       const int key,
                       const int /*scancode*/,
                       const int action,
                       const int /*mods*/)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(win, GLFW_TRUE);
	} else {
		static bool wireframe_on = false;
		if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
			wireframe_on = !wireframe_on;
			set_wireframe_mode(wireframe_on);
		}
	}
}


} // namespace gp

