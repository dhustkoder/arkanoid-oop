#include <iostream>
#include "exception.hpp"
#include "keyboard.hpp"
#include "display.hpp"


namespace gp {


Display::Display(const char* const name, const int width, const int height)
{
	if (!glfwInit())
		throw Exception("failed to initialize GLFW");

	m_window = glfwCreateWindow(width, height, name, nullptr, nullptr);

	if (m_window == nullptr)
		throw Exception("failed to initialize display");

	glfwMakeContextCurrent(m_window);
	glfwSetKeyCallback(m_window, Keyboard::keyCallback);
	glfwSetWindowSizeCallback(m_window, Display::resizeCallback);

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


Display::~Display()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}


void Display::resizeCallback(GLFWwindow* const /*window*/, const int width, const int height)
{
	glViewport(0, 0, width, height);
}


} // namespace gp
