#include <stdio.h>
#include "display.hpp"

namespace gp {

static Display s_display;

Display* create_display(const char* const title, const int w, const int h)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		goto free_sdl;

	if (SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8) != 0 ||
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8) != 0 ||
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8) != 0 ||
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8) != 0 ||
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32) != 0 ||
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) != 0)
		goto free_sdl;

	s_display.win = SDL_CreateWindow(title,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		w, h, SDL_WINDOW_OPENGL);

	if (s_display.win == nullptr)
		goto free_sdl;

	s_display.glcontext = SDL_GL_CreateContext(s_display.win);

	if (s_display.glcontext == nullptr)
		goto free_window;

	if (glewInit() != GLEW_OK)
		goto free_glcontext;

	return &s_display;

free_glcontext:
	SDL_GL_DeleteContext(s_display.glcontext);
free_window:
	SDL_DestroyWindow(s_display.win);
free_sdl:
	SDL_Quit();
	fprintf(stderr, "%s\n", SDL_GetError());
	return nullptr;
}

void destroy_display(Display* const display)
{
	SDL_GL_DeleteContext(display->glcontext);
	SDL_DestroyWindow(display-win);
	SDL_Quit();
}


bool update_display(Display* const display)
{
	SDL_GL_SwapWindow(display->win);
	while (SDL_PollEvent(&display->events)) {
		switch (display->events.type) {
		case SDL_QUIT: return false; break;
		}
	}

	return true;
}

} // namespace gp

