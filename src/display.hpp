#ifndef GPRO_DISPLAY_H_
#define GPRO_DISPLAY_H_
#include <GL/glew.h>
#include "SDL.h"

namespace gp {

struct Display {
	SDL_Window* win;
	SDL_GLContext glcontext;
	SDL_Event events;
};

extern Display* create_display(const char* title, int w, int h);
extern void destroy_display(Display* display);
extern bool update_display(Display* display);

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
