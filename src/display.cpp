#include <stdio.h>
#include "display.hpp"
#include "finally.hpp"

namespace gp {


GLFWwindow* glfw_window = nullptr;
Color clear_color { 0.0f, 0.0f, 0.0f, 1.0f };

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);

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

	glfwSetErrorCallback(&error_callback);

	if (glfwInit() != GLFW_TRUE)
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

	glfwSetKeyCallback(glfw_window, &key_callback);
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
	printf("KEY: %d\nACTION: %d\n", key, action);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(win, GLFW_TRUE);

	
	const auto inc = [] (float& col) {
		if (col < 1.0f)
			col += 0.10f;
	};

	const auto dec = [] (float& col) {
		if (col > 0.0f)
			col -= 0.10f;
	};

	switch (key) {
	case GLFW_KEY_UP: inc(clear_color.r); break;
	case GLFW_KEY_DOWN: dec(clear_color.r); break;
	case GLFW_KEY_RIGHT: inc(clear_color.g); break;
	case GLFW_KEY_LEFT: dec(clear_color.g); break;
	case GLFW_KEY_ENTER: inc(clear_color.b); break;
	case GLFW_KEY_BACKSPACE: dec(clear_color.b); break;
	}
}


} // namespace gp

