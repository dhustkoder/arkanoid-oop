#ifndef GPROJ_DISPLAY_HPP_
#define GPROJ_DISPLAY_HPP_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "color.hpp"

namespace gp {
	
extern bool init_display(const char* title, int w, int h);
extern void close_display();

inline void set_display_vsync(const bool vsync)
{
	glfwSwapInterval(vsync ? 1 : 0);
}

inline bool update_display()
{
	extern GLFWwindow* glfw_window;
	glfwPollEvents();
	glfwSwapBuffers(glfw_window);
	return glfwWindowShouldClose(glfw_window) == 0;
}

inline void clear_display(const Color& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}


} // namespace gp
#endif
