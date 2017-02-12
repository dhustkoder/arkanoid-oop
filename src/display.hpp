#ifndef ARKANOID_OOP_DISPLAY_HPP_
#define ARKANOID_OOP_DISPLAY_HPP_
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "exception.hpp"

namespace gp {


class Display {
public:
	static constexpr const int kDefaultWidth = 800;
	static constexpr const int kDefaultHeight = 600;
	static constexpr const char* const kDefaultTitle = "Arkanoop";

	static void initialize();
	static void terminate();
	static void setTitle(const std::string& name);
	static void setSize(int width, int height);
	static bool shouldClose();
	static void setVsync(bool value);
	static void update();
	static void clear(float r, float g, float b, float a);

private:
	static void resizeCallback(GLFWwindow* window, int width, int height);

private:
	static GLFWwindow* s_window;
	static int s_width;
	static int s_height;
	static Display s_instance;
};


inline void Display::setTitle(const std::string& name)
{
	glfwSetWindowTitle(s_window, name.c_str());
}


inline void Display::setSize(const int width, const int height)
{
	s_width = width;
	s_height = height;
	glfwSetWindowSize(s_window, width, height);
}


inline bool Display::shouldClose()
{
	return glfwWindowShouldClose(s_window) == 1;
}


inline void Display::setVsync(const bool value)
{
	glfwSwapInterval(static_cast<int>(value));
}


inline void Display::update()
{
	const GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		throw Exception((char*)glewGetErrorString(err));

	glfwSwapBuffers(s_window);
	glfwPollEvents();
}


inline void Display::clear(const float r, const float g, const float b, const float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}


} // namespace gp
#endif

