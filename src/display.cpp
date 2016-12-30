#include <stdio.h>
#include "display.hpp"

namespace gp {


GLFWwindow* window = nullptr;
static void glfw_error_callback(int error, const char* description);

bool init_display(const char* const title, const int w, const int h)
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

	if (glfwInit() == 0)
		return false;

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(w, h, title, NULL, NULL);

	if (window == nullptr)
		goto free_glfw;
	
	glfwMakeContextCurrent(window);

	if ((errcode = glewInit()) != GLEW_OK) {
		fprintf(stderr, "%s\n", glewGetErrorString(errcode));
		goto free_window;
	}

	puts("OpenGL");
	for (size_t i = 0; i < infosize; ++i)
		printf("%s: %s\n", infostrs[i], glGetString(infonums[i]));

	glfwSwapInterval(0);
	return true;

free_window:
	glfwDestroyWindow(window);
free_glfw:
	glfwTerminate();
	return false;
}

void close_display()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}


void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}

} // namespace gp

