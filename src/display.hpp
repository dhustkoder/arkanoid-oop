#ifndef GPRO_DISPLAY_HPP_
#define GPRO_DISPLAY_HPP_
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace gp {

struct Display {
	GLFWwindow* window;
};

extern Display* create_display(const char* title, int w, int h);
extern void destroy_display(Display* display);


inline bool update_display(Display* const display)
{
	glfwPollEvents();
	glfwSwapBuffers(display->window);
	return glfwWindowShouldClose(display->window) == 0;
}

inline void clear_display(const float r,
                          const float g,
                          const float b,
                          const float a,
                          Display* const /*display*/)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}


} // namespace gp
#endif
