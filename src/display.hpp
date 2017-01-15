#ifndef GPROJ_DISPLAY_HPP_
#define GPROJ_DISPLAY_HPP_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "math_types.hpp"

namespace gp {

using KeyCallback = void(*)(void* userdata, int key, int action);
constexpr const long kMaxKeyCallbacks = 1;

extern bool initialize_display(const char* title, int w, int h);
extern void terminate_display();
extern bool add_keycallback(void* userdata, KeyCallback callback);


inline void set_vsync(const bool vsync_on)
{
	glfwSwapInterval(static_cast<int>(vsync_on));
}


inline bool update_display()
{
	extern GLFWwindow* glfw_window;
	glfwPollEvents();
	glfwSwapBuffers(glfw_window);
	return glfwWindowShouldClose(glfw_window) == 0;
}


inline void clear_display(const Vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


} // namespace gp
#endif

