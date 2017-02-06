#include "keyboard.hpp"


namespace gp {

	
bool Keyboard::s_keys[1024] { false };


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
