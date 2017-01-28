#ifndef GPROJ_KEYBOARD_HPP_
#define GPROJ_KEYBOARD_HPP_

struct GLFWwindow;

namespace gp {

class Keyboard {
public:
	static bool isKeyPressed(int key);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	static bool s_keys[1024];
};



} // namespace gp
#endif
