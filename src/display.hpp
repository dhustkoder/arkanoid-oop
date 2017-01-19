#ifndef GPROJ_DISPLAY_HPP_
#define GPROJ_DISPLAY_HPP_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "math_types.hpp"

namespace gp {


extern bool initialize_display(const char* title, int w, int h);
extern void terminate_display();


inline void set_vsync(const bool vsync_on)
{
	glfwSwapInterval(static_cast<int>(vsync_on));
}


inline bool update_display()
{
	extern GLFWwindow* window;
	glfwPollEvents();
	glfwSwapBuffers(window);
	return glfwWindowShouldClose(window) == 0;
}


inline void clear_display(const Vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


inline void get_cursor_pos(Vec2* const res)
{
	extern GLFWwindow* window;

	double dx, dy;
	
	glfwGetCursorPos(window, &dx, &dy);

	res->x = static_cast<float>(dx);
	res->y = static_cast<float>(dy);
}


inline bool is_key_pressed(const int key)
{
	extern bool keystate[1024];
	return keystate[key];
}


} // namespace gp
#endif

