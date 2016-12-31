#include <stdio.h>
#include "display.hpp"
#include "finally.hpp"

namespace gp {


GLFWwindow* glfw_window = nullptr;

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

	auto glfw_guard = finally([] {
		glfwTerminate();
	});

	
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfw_window = glfwCreateWindow(w, h, title, NULL, NULL);

	if (glfw_window == nullptr)
		return false;

	auto glfw_window_guard = finally([] {
		glfwDestroyWindow(glfw_window);
	});
	

	glfwMakeContextCurrent(glfw_window);

	if ((errcode = glewInit()) != GLEW_OK) {
		fprintf(stderr, "%s\n", glewGetErrorString(errcode));
		return false;
	}

	puts("OpenGL");
	for (size_t i = 0; i < infosize; ++i)
		printf("%s: %s\n", infostrs[i], glGetString(infonums[i]));

	glfw_guard.Abort();
	glfw_window_guard.Abort();
	return true;
}

void close_display()
{
	glfwDestroyWindow(glfw_window);
	glfwTerminate();
}

void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}


} // namespace gp

