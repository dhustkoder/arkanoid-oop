#include <iostream>
#include "exception.hpp"
#include "keyboard.hpp"
#include "display.hpp"


namespace gp {

GLFWwindow* Display::s_window;
int Display::s_width = Display::kDefaultWidth;
int Display::s_height = Display::kDefaultHeight;
Display Display::s_instance;


void Display::initialize()
{
	if (!glfwInit())
		throw Exception("failed to initialize GLFW");

	s_window = glfwCreateWindow(s_width, s_height, kDefaultTitle, nullptr, nullptr);

	if (s_window == nullptr)
		throw Exception("failed to initialize display");

	glfwMakeContextCurrent(s_window);
	glfwSetKeyCallback(s_window, Keyboard::keyCallback);
	glfwSetWindowSizeCallback(s_window, Display::resizeCallback);

	const int glew_err = glewInit();
	if (glew_err != GLEW_OK)
		throw Exception((char*)glewGetErrorString(glew_err));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	constexpr const int info_size = 4;
	constexpr GLenum info_enums[info_size] {
		GL_VENDOR, GL_RENDERER, GL_VERSION,
		GL_SHADING_LANGUAGE_VERSION
	};
	constexpr const char* const info_strs[info_size] {
		"VENDOR", "RENDERER", "VERSION",
		"SHADING LANGUAGE VERSION"
	};

	std::cout << "OpenGL\n";
	for (int i = 0; i < info_size; ++i)
		printf("%s: %s\n", info_strs[i], glGetString(info_enums[i]));
}


void Display::terminate()
{
	glfwDestroyWindow(s_window);
	glfwTerminate();
}


void Display::resizeCallback(GLFWwindow* const /*window*/, const int width, const int height)
{
	glViewport(0, 0, width, height);
}


} // namespace gp
