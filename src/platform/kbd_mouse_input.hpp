#ifndef GPROJ_KBD_MOUSE_INPUT_HPP_
#define GPROJ_KBD_MOUSE_INPUT_HPP_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "math/math_types.hpp"

namespace gp {


inline Vec2 get_cursor_pos()
{
	extern GLFWwindow* window;
	double dx, dy;
	glfwGetCursorPos(window, &dx, &dy);
	return { static_cast<float>(dx), static_cast<float>(dy) };
}


inline bool is_key_pressed(const int key)
{
	extern bool keystate[1024];
	return keystate[key];
}


} // namespace gp
#endif

