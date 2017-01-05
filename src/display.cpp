#include <stdio.h>
#include "display.hpp"
#include "finally.hpp"

namespace gp {

GLFWwindow* glfw_window = nullptr;
static KeyCallback key_callbacks[kMaxKeyCallbacks] { nullptr };
static void* key_callbacks_userdata[kMaxKeyCallbacks] { nullptr };
static long key_callbacks_count = 0;


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

	auto glfw_guard = finally([] {
		glfwTerminate();
	});
	
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfw_window = glfwCreateWindow(w, h, title, NULL, NULL);

	if (glfw_window == nullptr)
		return false;

	auto glfw_window_guard = finally([] {
		glfwDestroyWindow(glfw_window);
		glfw_window = nullptr;
	});

	glfwSetKeyCallback(glfw_window, &glfw_key_callback);
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


void terminate_display()
{
	glfwDestroyWindow(glfw_window);
	glfwTerminate();
	glfw_window = nullptr;
	key_callbacks_count = 0;
}


bool add_keycallback(void* const userdata, const KeyCallback callback)
{
	if (key_callbacks_count < kMaxKeyCallbacks) {
		key_callbacks[key_callbacks_count] = callback;
		key_callbacks_userdata[key_callbacks_count] = userdata;
		++key_callbacks_count;
		return true;
	}

	return false;
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
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(win, GLFW_TRUE);
	for (long i = 0; i < key_callbacks_count; ++i)
		key_callbacks[i](key_callbacks_userdata[i], key, action);
}


} // namespace gp

