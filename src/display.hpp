#ifndef GPROJ_DISPLAY_HPP_
#define GPROJ_DISPLAY_HPP_
#include <stdexcept>

struct GLFWwindow;


namespace gp {

class Display {
public:
	Display(const char* name, int width, int height);
	~Display();
	bool shouldClose() const;
	void update();
	void clear(float r, float g, float b, float a);

	static void resizeCallback(GLFWwindow* window, int width, int height);
private:
	GLFWwindow* m_window;
};


} // namespace gp
#endif
