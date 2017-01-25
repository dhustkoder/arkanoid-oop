#ifndef GPROJ_DISPLAY_HPP_
#define GPROJ_DISPLAY_HPP_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "math/math_types.hpp"

namespace gp {


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


} // namespace gp
#endif

