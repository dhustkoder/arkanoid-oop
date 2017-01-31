#ifndef GPROJ_DISPLAY_HPP_
#define GPROJ_DISPLAY_HPP_
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace gp {

class Display {
public:
	Display(const char* name, int width, int height);
	~Display();
	bool shouldClose() const;
	void setVsync(bool value);
	void update();
	void clear(float r, float g, float b, float a);
private:
	static void resizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* m_window;
};


inline bool Display::shouldClose() const
{
	return glfwWindowShouldClose(m_window) == 1;
}


inline void Display::setVsync(const bool value)
{
	glfwSwapInterval(static_cast<int>(value));
}


inline void Display::update()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}


inline void Display::clear(const float r, const float g, const float b, const float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


} // namespace gp
#endif

