#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "keyboard.hpp"


namespace gp {

	
bool Keyboard::s_keys[1024] { false };


bool Keyboard::isKeyPressed(const int key)
{
	return s_keys[key];
}


void Keyboard::keyCallback(GLFWwindow* const window,
                           const int key,
                           const int /*scancode*/,
                           const int action,
                           int /*mods*/)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	else
		s_keys[key] = action != GLFW_RELEASE;
}


} // namespace gp
