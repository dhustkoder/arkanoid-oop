#ifndef ARKANOOP_KEYBOARD_HPP_
#define ARKANOOP_KEYBOARD_HPP_
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace gp {


class Keyboard {
public:
	enum Key {
		W = GLFW_KEY_W,
		S = GLFW_KEY_S,
		D = GLFW_KEY_D,
		A = GLFW_KEY_A
	};

	static bool isKeyPressed(Key key);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	static bool s_keys[1024];
};



inline bool Keyboard::isKeyPressed(const Keyboard::Key key)
{
	return s_keys[key];
}


} // namespace gp
#endif
