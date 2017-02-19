#ifndef ARKANOOP_DISPLAY_HPP_
#define ARKANOOP_DISPLAY_HPP_
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "exception.hpp"
#include "math_types.hpp"

namespace gp {


class Display {
public:
	static constexpr const int kDefaultScreenWidth = 800;
	static constexpr const int kDefaultScreenHeight = 600;
	static constexpr const int kDefaultViewWidth = 800;
	static constexpr const int kDefaultViewHeight = 600;
	static constexpr auto kDefaultTitle = u8"Arkanoop";

	Display() = delete;

	static void initialize();
	static void terminate();
	static void setTitle(const std::string& name);
	
	static void setScreenSize(int width, int height);
	static Vec2f getScreenSize();
	static Vec2f getViewSize();

	static bool shouldClose();
	static void setVsync(bool value);
	static void update();
	static void clear(float r, float g, float b, float a);

private:
	static void resizeCallback(GLFWwindow* window, int width, int height);

private:
	static GLFWwindow* s_window;
	
	static int s_screenWidth;
	static int s_screenHeight;
	
	static int s_viewWidth;
	static int s_viewHeight;
};


inline void Display::setTitle(const std::string& name)
{
	glfwSetWindowTitle(s_window, name.c_str());
}


inline void Display::setScreenSize(const int width, const int height)
{
	s_screenWidth = width;
	s_screenHeight = height;
	glfwSetWindowSize(s_window, width, height);
}


inline Vec2f Display::getScreenSize()
{
	return { s_screenWidth, s_screenHeight };
}


inline Vec2f Display::getViewSize()
{
	return { s_viewWidth, s_viewHeight };
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

