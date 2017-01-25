#include "renderer/renderer.hpp"
#include "kbd_mouse_input.hpp"

namespace gp {


bool keystate[1024] { false };


void kbd_callback(GLFWwindow* const win, int key, int scancode, int action, int mods);
void cursor_callback(GLFWwindow* win, double x, double y);


void kbd_callback(GLFWwindow* const win,
                  const int key,
                  const int /*scancode*/,
                  const int action,
                  const int /*mods*/)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(win, GLFW_TRUE);
	} else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		static bool wireframe_on = false;
		wireframe_on = !wireframe_on;
		set_wireframe_mode(wireframe_on);
	} else {
		keystate[key] = action != GLFW_RELEASE;
	}
}


} // namespace gp
