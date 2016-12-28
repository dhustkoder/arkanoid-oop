#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "display.hpp"

int main(int /*argc*/, char** /*argv*/)
{
	gp::Display* const display = gp::create_display("Hello gproj!", 800, 600);
	if (display == nullptr)
		return EXIT_FAILURE;

	constexpr const auto kTurnTicks = 856ul;
	unsigned long ticks = SDL_GetTicks();
	float r = 0, g = 0, b = 0;
	float* p[3] { &r, &g, &b };

	while (update_display(display)) {
		const auto passed = SDL_GetTicks() - ticks;
		if (passed > kTurnTicks) {
			const auto ticks_sqrt = sqrtf(ticks);
			*p[0] = sinf(M_PI * 2 + passed);
			*p[1] = cosf(r);
			*p[2] = sinf(sqrtf(M_PI * 2 + ticks_sqrt));
			float* const aux = p[0];
			p[0] = p[1];
			p[1] = p[2];
			p[2] = aux;
			ticks = SDL_GetTicks();
		}
		gp::clear_display(r, g, b, 1.0f, display);
	}

	gp::destroy_display(display);
	return EXIT_SUCCESS;
}



